#### [kvm-unit-tests PATCH 2/2] Use a status enum for reporting pass/failFrom: Bill Wendling <morbo@google.com>
##### From: Bill Wendling <morbo@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bill Wendling <morbo@google.com>
X-Patchwork-Id: 11186711
Return-Path: <SRS0=yg+T=YF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 226B21709
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 12 Oct 2019 08:20:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id ED3B120673
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 12 Oct 2019 08:20:23 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="RRhy1dxu"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728060AbfJLIUV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 12 Oct 2019 04:20:21 -0400
Received: from mail-pg1-f201.google.com ([209.85.215.201]:44386 "EHLO
        mail-pg1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726821AbfJLIUV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 12 Oct 2019 04:20:21 -0400
Received: by mail-pg1-f201.google.com with SMTP id z7so8624735pgk.11
        for <kvm@vger.kernel.org>; Sat, 12 Oct 2019 01:20:20 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=rOseJJCccx3BXbm8CgRKxIjZpwpktd5KdYgAOg8B8/A=;
        b=RRhy1dxupblwHgfUSaSASGlWUlPCu3Tb/qpehXDWEkLfM2gmN70yWulMLYahTlCBVG
         OB62bFiMSlX2ii4EFInumZgGZMrGdbGxOOZhzqhTS1/4DLbrv9sJjfxGAFYpWlDBpDUV
         ojtG8qUsY/uqz9wh1a5vP0HgvcxRe8EqzlqKZWI6O+6nm9d6vzFcZulrwPYyxNfelr17
         voeJ1IFoAopxwymvkNUDkNJP0jIQ4kgBLlbmtfxJubGKf0J25PAcOlA5iRu3VDKq6odj
         0ZkOjF6h1ZMTp/fxn5xObOWFDK5KnsuWrdEDkrxiPs+G3R/FoItwxsTUfxOxcrgCQzwZ
         lEVQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=rOseJJCccx3BXbm8CgRKxIjZpwpktd5KdYgAOg8B8/A=;
        b=AeHxw1Yrr2NNem3WyR1fP2Y+v3QpZljyTDn7d0XX1dQbLEZbZ6KokWWXRI1DMaoG7k
         a0LG9Gp5Wy0Cfm/irB6CvS9WWviCZz4M9EK9H1tNiYFovMOgwdcGNeo3rNZ6OVfcsVA9
         ttMX3O44mkzod0VeqxI/TSxT6zdh+BsH6iIBfjIpbUwOro5APDC4ugqBVtTW4wA9HR0h
         47JzQEiFPJXtyLl6n24BNB2MnGTk9ZgQJLZDdT+sHDCE+kmKiXcTLy2aLCJPQTHjPzNX
         Ef1pNh+OMTElrIeJfEHUdreAACs0phMFViL9ldhz2KxQ4tEJgxDaLL8DcBl9CcwT7qlC
         YHjg==
X-Gm-Message-State: APjAAAX3fSf7i9sttHApW1RJh9mnzdJ+77YoYhq8ff6dEutGAy6W1/0C
        mSZW8aZ+Cfplc86Z2XAZcm5x0Gmxj2Ov1VxkVjHAK1STER2r8mXMjs6xtmJwXkWeKwpqb5mScKp
        Zv+mhICJ8+TdNO11eonkMFgK6QxjQWAXwYQSMyhJs8+7YnexiRjm1qw==
X-Google-Smtp-Source: 
 APXvYqwlzzolXzxit6WcEKfVzjjviTWu3HKyKqEjuDmMG6w576LSgRG8HbwuoYMhfI+jOX0A/ihrlEEgyg==
X-Received: by 2002:a65:5249:: with SMTP id q9mr15158097pgp.390.1570868420101;
 Sat, 12 Oct 2019 01:20:20 -0700 (PDT)
Date: Sat, 12 Oct 2019 01:20:15 -0700
In-Reply-To: <20191012074454.208377-1-morbo@google.com>
Message-Id: <20191012082015.247954-1-morbo@google.com>
Mime-Version: 1.0
References: <20191012074454.208377-1-morbo@google.com>
X-Mailer: git-send-email 2.23.0.700.g56cf767bdb-goog
Subject: [kvm-unit-tests PATCH 2/2] Use a status enum for reporting pass/fail
From: Bill Wendling <morbo@google.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: jmattson@google.com, Bill Wendling <morbo@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Some values passed into "report" as "pass/fail" are larger than the
size of the parameter. Use instead a status enum so that the size of the
argument no longer matters.

Signed-off-by: Bill Wendling <morbo@google.com>
---
 lib/libcflat.h | 14 ++++++++++++--
 lib/report.c   | 24 ++++++++++++------------
 2 files changed, 24 insertions(+), 14 deletions(-)

```
#### [kvm-unit-tests PATCH 1/1] pci: use uint64_t for unsigned long valuesFrom: Bill Wendling <morbo@google.com>
##### From: Bill Wendling <morbo@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bill Wendling <morbo@google.com>
X-Patchwork-Id: 11186713
Return-Path: <SRS0=yg+T=YF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CE1581709
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 12 Oct 2019 08:27:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A1B26206A1
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 12 Oct 2019 08:27:14 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="kbHL3GIf"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728927AbfJLI02 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 12 Oct 2019 04:26:28 -0400
Received: from mail-pf1-f201.google.com ([209.85.210.201]:55520 "EHLO
        mail-pf1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728886AbfJLI02 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 12 Oct 2019 04:26:28 -0400
Received: by mail-pf1-f201.google.com with SMTP id u21so6420811pfm.22
        for <kvm@vger.kernel.org>; Sat, 12 Oct 2019 01:26:28 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=mE3OAeOE/eYuT5ARQUE6mDRHkwycMi2Fh29zXTPw2/A=;
        b=kbHL3GIfkJgldeU+DhHMBH2y8H7A2yBAorSwuDzUCWdBceeDijoKWTqJx0SUtmgXBG
         28PgdlKbGSc+PODN7x1v1GBxUqQ1x8HoVmi64/LNEf/eIKm44YURxqTeRodAVaj+xd4s
         +BAFAw47eI1eAv69Q9s4QJjxHk+ZGKLVtuBfwm9FLwUmPAgp6ImKLrWn4eN+2hOq3waX
         AoWZGSo3JiOCVkPF+uGM5T0OBTk61Q16pOOEVeslq+3dvQWykUbgw0JOMjEzdK+tcjz1
         EyxkqMlWvlshGEobgM9LU1kN+52noICVpQjc2as2Id1ybH24RiQfmRA1bHhZrDJOMzAl
         fa7w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=mE3OAeOE/eYuT5ARQUE6mDRHkwycMi2Fh29zXTPw2/A=;
        b=rEsQmXXXgxF8WvuxEaTl5C9kBk1OwlY7eM/F24HYaoipauw1/nSLTGj1+2HI/O0s8E
         vIB2CcwK/S/Pa8ZEpVTYaNDMN3I+hPmmzF0XF5eujiZFtYAs8Jq7zTjSHW6WnqsvHL2k
         Fo5yr+7Xm1qCNGTLQUhP9hecjkXmBhCU/isgokaoALtFceUOV+eviuA09cvac+nUO9jP
         8bhLrZ/DgDjxJUv/jKkaG1oQrTxgcTMmvqq3IkY2/1K4kNy3scp3gFrENqkiETvLlj76
         oy4YWTOjl2R74Lf4d9J1pHap0htu0r6Fv1nWghKk2TWs2jGvw/lvCSs+GbQTOtmmsQyj
         r7HQ==
X-Gm-Message-State: APjAAAVubdWolNlbPJ0Md/+N9CAj2DYyGKE5sHzHy19GxAxpI+hfx7Bq
        wwrlk7IlsVnFZyprje3iDbxDUTJOaS4ZtXGtxx1D1scpA27S7xNepFcaQS39FZ8KfiKzVQwm9yO
        nK3ak2Ew0KfRGJniuCWH2+ODsr2cwzTdzEWy+D7xO4fgXKG5Y5nHKaQ==
X-Google-Smtp-Source: 
 APXvYqzkv5IT+m8HeDRkDddUX/rYRW6cGmJw/DYW9p/YGkuLUwtd3wS6ODZp6QTbTyfqh1emcLZRxKHFag==
X-Received: by 2002:a65:685a:: with SMTP id q26mr3471031pgt.32.1570868787641;
 Sat, 12 Oct 2019 01:26:27 -0700 (PDT)
Date: Sat, 12 Oct 2019 01:26:23 -0700
In-Reply-To: <81990077-23b0-b150-1373-2bb5734d4f23@arm.com>
Message-Id: <20191012082623.249497-1-morbo@google.com>
Mime-Version: 1.0
References: <81990077-23b0-b150-1373-2bb5734d4f23@arm.com>
X-Mailer: git-send-email 2.23.0.700.g56cf767bdb-goog
Subject: [kvm-unit-tests PATCH 1/1] pci: use uint64_t for unsigned long values
From: Bill Wendling <morbo@google.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com, alexandru.elisei@arm.com
Cc: jmattson@google.com, Bill Wendling <morbo@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The "pci_bar_*" functions use 64-bit masks, but the results are assigned
to 32-bit variables. Use 32-bit masks, since we're interested only in
the least significant 4-bits.

Signed-off-by: Bill Wendling <morbo@google.com>
---
 lib/linux/pci_regs.h | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [kvm-unit-tests PATCH 1/2] Use a status enum for reporting pass/failFrom: Bill Wendling <morbo@google.com>
##### From: Bill Wendling <morbo@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bill Wendling <morbo@google.com>
X-Patchwork-Id: 11186705
Return-Path: <SRS0=yg+T=YF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2A7351575
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 12 Oct 2019 07:45:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0846C2190F
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 12 Oct 2019 07:45:02 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="nwK2aSbt"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728410AbfJLHpB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 12 Oct 2019 03:45:01 -0400
Received: from mail-pg1-f202.google.com ([209.85.215.202]:43217 "EHLO
        mail-pg1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726728AbfJLHpA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 12 Oct 2019 03:45:00 -0400
Received: by mail-pg1-f202.google.com with SMTP id 6so8576110pgi.10
        for <kvm@vger.kernel.org>; Sat, 12 Oct 2019 00:44:59 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=WmdqpqGfkHn4HPcnbsc3aPPkFBnc3wfZ29QxdaymD6w=;
        b=nwK2aSbtoqORtQUaZTLKj/N7XBRh/Tee1SjTjrgicpibjHL/sA3aN8BNQW060Xu9Dw
         H5hoPRt7QNnEiuBDJ/IM0qHla/3Lc5WZIlxzN/yWm70BX0cUhjMumZv6M43fqcFXwDIH
         kdPmNA3ZHAJTAO78J0YbZlbRFmlmDcJ6MTspHNfabQVRFCHqxuHiGa+sU4WKtpr4CAdS
         F7iYVhOHpbA6LnhrnWNFfnNiD6QMjwA5c9yxH8HmxNtnHkqRzD5E+GcbiTFmOi6GGoWB
         +N6K3Q+kJww2QkphfpBHqHGn2/glEKCXOMUwePWCuebXv9r9KQVoILh9ZWk5Oea9kwy4
         Mrdw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=WmdqpqGfkHn4HPcnbsc3aPPkFBnc3wfZ29QxdaymD6w=;
        b=dZU+dFOD06IgZdnsYJf9eo3BgwhMgUr1PmhmYE7fqHoF0cwY2xnOpUF7pU2xUvhbLc
         RBBiMzvO3MfZkikEGEaN8G7jWZSr0hs5e6PUlIyJYw7Yn/m14p+JPqgNbe8c5ZmRqBD1
         o/GDNjLUhh+Lk4+AwMSwUVggGudQc0IssCmIb2IUGiQamgsq6zoSz8V4UJ+F3evHvgMQ
         nEiUDA+YKRifEGJa2Be4wfCknQJRk6ZyEQtuxlqZsw84QLtwC63B/zTkqcPettOosm3L
         mK+Te2mbc19ZF4awwhjw8RFDPc7Jz5K/Ql+jpuCDjKOIJz05xy/cIlZ8PBWa89I/KEoR
         LhlQ==
X-Gm-Message-State: APjAAAVWoVD9zj4oxUIZYcR8K/sF+U4nz/owpLoPdmpFi6uF9+Sa5/ZR
        Zh3+TLmfVA/fi0JbE3BCeaSUtei790SsmPVXV8zw0g0hOzgGy9Oytk4ucco0zzRm+EdP8LGSQKP
        L/231i30a10Ufv6rZj6Pls+UIckasYytMB2jRw2tVnaA7TdfIhRQ0Gw==
X-Google-Smtp-Source: 
 APXvYqxGA7vqboZv8LTKMJ/xrapYf/RkHLED3rrKm5GU+GC1TlCDQgppBsJg1KZqirPrQFUXV99T8Yk4VA==
X-Received: by 2002:a63:2484:: with SMTP id
 k126mr20840500pgk.331.1570866298519;
 Sat, 12 Oct 2019 00:44:58 -0700 (PDT)
Date: Sat, 12 Oct 2019 00:44:53 -0700
Message-Id: <20191012074454.208377-1-morbo@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.23.0.700.g56cf767bdb-goog
Subject: [kvm-unit-tests PATCH 1/2] Use a status enum for reporting pass/fail
From: Bill Wendling <morbo@google.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: jmattson@google.com, Bill Wendling <morbo@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Some values passed into "report" as "pass/fail" are larger than the
size of the parameter. Instead use a status enum so that the size of the
argument no longer matters.

Signed-off-by: Bill Wendling <morbo@google.com>
---
 lib/libcflat.h | 13 +++++++++++--
 lib/report.c   | 24 ++++++++++++------------
 2 files changed, 23 insertions(+), 14 deletions(-)

```
#### [PATCH] target/i386/kvm: Add Hyper-V direct tlb flush support
##### From: lantianyu1986@gmail.com

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tianyu Lan <lantianyu1986@gmail.com>
X-Patchwork-Id: 11186601
Return-Path: <SRS0=yg+T=YF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8834F76
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 12 Oct 2019 03:42:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5CB7D2067B
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 12 Oct 2019 03:42:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="lqpvzdog"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728478AbfJLDmG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 11 Oct 2019 23:42:06 -0400
Received: from mail-pg1-f194.google.com ([209.85.215.194]:34431 "EHLO
        mail-pg1-f194.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726982AbfJLDmG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 11 Oct 2019 23:42:06 -0400
Received: by mail-pg1-f194.google.com with SMTP id y35so6880068pgl.1
        for <kvm@vger.kernel.org>; Fri, 11 Oct 2019 20:42:05 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=GZeFYLsCbWX3apu2MdiEFh9Sy8YdIPqXB58kHqtr/Y8=;
        b=lqpvzdognJAYXQUoX6/ALFsg7p1Yo6zo7/1SUDSjsQgWcjMp4iOgapdSBAGwIppui0
         lP6l5l6JvLKfT13BHWz4U5EbLEMOzgXcXVp20NHJG/vDj6U8ccNjNtnCroDifS2kqY5P
         mHt47mDoV1nTT+R5jE9BvUd8d2+igUFQGP92UOI0EVDvF8wGgS1N83lTHQzXztSjP1lh
         ws2p9jb99kiQi12LrHikeQ9iu2sIteL2iVQ8oVwyIhmglwGAV3mBzlQHzy8XtgmwmBRs
         DWItLSdE8Lzr33AwaKXRp73H+TOdikGr1s1MpxDZDUtow9dyiM4Podw8HSLaxA/eT9Ew
         76+g==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=GZeFYLsCbWX3apu2MdiEFh9Sy8YdIPqXB58kHqtr/Y8=;
        b=fXBFUUe7uTB9DPwNnkhzGfr+ebnBO0Hk6BA1uJbt/1Sl6oQgmtBCDTYn6dsvIG9G29
         8vrz7Dzl1inxw/VUHSTH+jqP5/2pKSIllpOznYxgXC7VMzstGq+DeR66ZjeQ1P8tOcRd
         zL2/0wvCo5L2/bzwfFs195kXljPHSUQhgpPDt06nnIRhyMVWE42bl+UgbXUBHwzunISM
         o2BLwH05xiuimhykgGJNDpMeLUYzRAVGu73WIE5pA84DttunygKQIg57U0rk+gaqOWVt
         7TeksXh/ObQxrrjvjCIt1uxszr8aVhIaipmYYiL1PcMVl8sdCPiQ6CHIlB9ABF981e+N
         OE3w==
X-Gm-Message-State: APjAAAWV057BR+DMHLsDzLv/nAxi7oZei0rFKKWkjxoOY5WGI6YMDKXG
        t0ReC6ghFTeo1LW3Xxf+qEo=
X-Google-Smtp-Source: 
 APXvYqwhCGJrhNIlOhl/+bRtU2W9TAdYBDoyIW3dkdjMr2gMMRKREEufY01eo/4AQPTNN0h7OGbduw==
X-Received: by 2002:a63:e013:: with SMTP id
 e19mr21341809pgh.274.1570851725070;
        Fri, 11 Oct 2019 20:42:05 -0700 (PDT)
Received: from localhost.corp.microsoft.com ([167.220.255.39])
        by smtp.googlemail.com with ESMTPSA id
 m34sm18129460pgb.91.2019.10.11.20.42.01
        (version=TLS1_2 cipher=ECDHE-RSA-CHACHA20-POLY1305 bits=256/256);
        Fri, 11 Oct 2019 20:42:04 -0700 (PDT)
From: lantianyu1986@gmail.com
X-Google-Original-From: Tianyu.Lan@microsoft.com
To: mst@redhat.com, cohuck@redhat.com, pbonzini@redhat.com,
        rth@twiddle.net, ehabkost@redhat.com, mtosatti@redhat.com,
        vkuznets@redhat.com
Cc: Tianyu Lan <Tianyu.Lan@microsoft.com>, qemu-devel@nongnu.org,
        kvm@vger.kernel.org
Subject: [PATCH] target/i386/kvm: Add Hyper-V direct tlb flush support
Date: Sat, 12 Oct 2019 11:41:53 +0800
Message-Id: <20191012034153.31817-1-Tianyu.Lan@microsoft.com>
X-Mailer: git-send-email 2.14.5
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Tianyu Lan <Tianyu.Lan@microsoft.com>

Hyper-V direct tlb flush targets KVM on Hyper-V guest.
Enable direct TLB flush for its guests meaning that TLB
flush hypercalls are handled by Level 0 hypervisor (Hyper-V)
bypassing KVM in Level 1. Due to the different ABI for hypercall
parameters between Hyper-V and KVM, KVM capabilities should be
hidden when enable Hyper-V direct tlb flush otherwise KVM
hypercalls may be intercepted by Hyper-V. Add new parameter
"hv-direct-tlbflush". Check expose_kvm and Hyper-V tlb flush
capability status before enabling the feature.

Signed-off-by: Tianyu Lan <Tianyu.Lan@microsoft.com>
---
 docs/hyperv.txt           | 12 ++++++++++++
 linux-headers/linux/kvm.h |  1 +
 target/i386/cpu.c         |  2 ++
 target/i386/cpu.h         |  1 +
 target/i386/kvm.c         | 21 +++++++++++++++++++++
 5 files changed, 37 insertions(+)

```
#### [PATCH v2] KVM: fix overflow of zero page refcount with ksm running
##### From: Zhuang Yanying <ann.zhuangyanying@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Zhuang Yanying <ann.zhuangyanying@huawei.com>
X-Patchwork-Id: 11186599
Return-Path: <SRS0=yg+T=YF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D1AC676
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 12 Oct 2019 03:38:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id BBD1021D80
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 12 Oct 2019 03:38:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726918AbfJLDiA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 11 Oct 2019 23:38:00 -0400
Received: from szxga07-in.huawei.com ([45.249.212.35]:33836 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726354AbfJLDiA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 11 Oct 2019 23:38:00 -0400
Received: from DGGEMS410-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id BCF21FAD66123068F06F;
        Sat, 12 Oct 2019 11:37:56 +0800 (CST)
Received: from localhost (10.133.215.230) by DGGEMS410-HUB.china.huawei.com
 (10.3.19.210) with Microsoft SMTP Server id 14.3.439.0; Sat, 12 Oct 2019
 11:37:49 +0800
From: Zhuang Yanying <ann.zhuangyanying@huawei.com>
To: <linfeng23@huawei.com>, <pbonzini@redhat.com>,
        <linux-kernel@vger.kernel.org>, <kvm@vger.kernel.org>
CC: <weiqi4@huawei.com>, <weidong.huang@huawei.com>,
        Zhuang Yanying <ann.zhuangyanying@huawei.com>
Subject: [PATCH v2] KVM: fix overflow of zero page refcount with ksm running
Date: Sat, 12 Oct 2019 11:37:31 +0800
Message-ID: <1570851452-23364-1-git-send-email-ann.zhuangyanying@huawei.com>
X-Mailer: git-send-email 1.9.5.msysgit.1
MIME-Version: 1.0
X-Originating-IP: [10.133.215.230]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We are testing Virtual Machine with KSM on v5.4-rc2 kernel,
and found the zero_page refcount overflow.
The cause of refcount overflow is increased in try_async_pf
(get_user_page) without being decreased in mmu_set_spte()
while handling ept violation.
In kvm_release_pfn_clean(), only unreserved page will call
put_page. However, zero page is reserved.
So, as well as creating and destroy vm, the refcount of
zero page will continue to increase until it overflows.

step1:
echo 10000 > /sys/kernel/pages_to_scan/pages_to_scan
echo 1 > /sys/kernel/pages_to_scan/run
echo 1 > /sys/kernel/pages_to_scan/use_zero_pages

step2:
just create several normal qemu kvm vms.
And destroy it after 10s.
Repeat this action all the time.

After a long period of time, all domains hang because
of the refcount of zero page overflow.

Qemu print error log as follow:
 …
 error: kvm run failed Bad address
 EAX=00006cdc EBX=00000008 ECX=80202001 EDX=078bfbfd
 ESI=ffffffff EDI=00000000 EBP=00000008 ESP=00006cc4
 EIP=000efd75 EFL=00010002 [-------] CPL=0 II=0 A20=1 SMM=0 HLT=0
 ES =0010 00000000 ffffffff 00c09300 DPL=0 DS   [-WA]
 CS =0008 00000000 ffffffff 00c09b00 DPL=0 CS32 [-RA]
 SS =0010 00000000 ffffffff 00c09300 DPL=0 DS   [-WA]
 DS =0010 00000000 ffffffff 00c09300 DPL=0 DS   [-WA]
 FS =0010 00000000 ffffffff 00c09300 DPL=0 DS   [-WA]
 GS =0010 00000000 ffffffff 00c09300 DPL=0 DS   [-WA]
 LDT=0000 00000000 0000ffff 00008200 DPL=0 LDT
 TR =0000 00000000 0000ffff 00008b00 DPL=0 TSS32-busy
 GDT=     000f7070 00000037
 IDT=     000f70ae 00000000
 CR0=00000011 CR2=00000000 CR3=00000000 CR4=00000000
 DR0=0000000000000000 DR1=0000000000000000 DR2=0000000000000000 DR3=0000000000000000
 DR6=00000000ffff0ff0 DR7=0000000000000400
 EFER=0000000000000000
 Code=00 01 00 00 00 e9 e8 00 00 00 c7 05 4c 55 0f 00 01 00 00 00 <8b> 35 00 00 01 00 8b 3d 04 00 01 00 b8 d8 d3 00 00 c1 e0 08 0c ea a3 00 00 01 00 c7 05 04
 …

Meanwhile, a kernel warning is departed.

 [40914.836375] WARNING: CPU: 3 PID: 82067 at ./include/linux/mm.h:987 try_get_page+0x1f/0x30
 [40914.836412] CPU: 3 PID: 82067 Comm: CPU 0/KVM Kdump: loaded Tainted: G           OE     5.2.0-rc2 #5
 [40914.836415] RIP: 0010:try_get_page+0x1f/0x30
 [40914.836417] Code: 40 00 c3 0f 1f 84 00 00 00 00 00 48 8b 47 08 a8 01 75 11 8b 47 34 85 c0 7e 10 f0 ff 47 34 b8 01 00 00 00 c3 48 8d 78 ff eb e9 <0f> 0b 31 c0 c3 66 90 66 2e 0f 1f 84 00 0
 0 00 00 00 48 8b 47 08 a8
 [40914.836418] RSP: 0018:ffffb4144e523988 EFLAGS: 00010286
 [40914.836419] RAX: 0000000080000000 RBX: 0000000000000326 RCX: 0000000000000000
 [40914.836420] RDX: 0000000000000000 RSI: 00004ffdeba10000 RDI: ffffdf07093f6440
 [40914.836421] RBP: ffffdf07093f6440 R08: 800000424fd91225 R09: 0000000000000000
 [40914.836421] R10: ffff9eb41bfeebb8 R11: 0000000000000000 R12: ffffdf06bbd1e8a8
 [40914.836422] R13: 0000000000000080 R14: 800000424fd91225 R15: ffffdf07093f6440
 [40914.836423] FS:  00007fb60ffff700(0000) GS:ffff9eb4802c0000(0000) knlGS:0000000000000000
 [40914.836425] CS:  0010 DS: 0000 ES: 0000 CR0: 0000000080050033
 [40914.836426] CR2: 0000000000000000 CR3: 0000002f220e6002 CR4: 00000000003626e0
 [40914.836427] DR0: 0000000000000000 DR1: 0000000000000000 DR2: 0000000000000000
 [40914.836427] DR3: 0000000000000000 DR6: 00000000fffe0ff0 DR7: 0000000000000400
 [40914.836428] Call Trace:
 [40914.836433]  follow_page_pte+0x302/0x47b
 [40914.836437]  __get_user_pages+0xf1/0x7d0
 [40914.836441]  ? irq_work_queue+0x9/0x70
 [40914.836443]  get_user_pages_unlocked+0x13f/0x1e0
 [40914.836469]  __gfn_to_pfn_memslot+0x10e/0x400 [kvm]
 [40914.836486]  try_async_pf+0x87/0x240 [kvm]
 [40914.836503]  tdp_page_fault+0x139/0x270 [kvm]
 [40914.836523]  kvm_mmu_page_fault+0x76/0x5e0 [kvm]
 [40914.836588]  vcpu_enter_guest+0xb45/0x1570 [kvm]
 [40914.836632]  kvm_arch_vcpu_ioctl_run+0x35d/0x580 [kvm]
 [40914.836645]  kvm_vcpu_ioctl+0x26e/0x5d0 [kvm]
 [40914.836650]  do_vfs_ioctl+0xa9/0x620
 [40914.836653]  ksys_ioctl+0x60/0x90
 [40914.836654]  __x64_sys_ioctl+0x16/0x20
 [40914.836658]  do_syscall_64+0x5b/0x180
 [40914.836664]  entry_SYSCALL_64_after_hwframe+0x44/0xa9
 [40914.836666] RIP: 0033:0x7fb61cb6bfc7

Signed-off-by: LinFeng <linfeng23@huawei.com>
Signed-off-by: Zhuang Yanying <ann.zhuangyanying@huawei.com>
---
v1 -> v2:  fix compile error
---
 virt/kvm/kvm_main.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH net-next 1/3] tuntap: reorganize tun_msg_ctl usage
##### From: prashantbhole.linux@gmail.com

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: prashantbhole.linux@gmail.com
X-Patchwork-Id: 11186539
Return-Path: <SRS0=yg+T=YF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DFFB914ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 12 Oct 2019 01:54:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id BABB621835
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 12 Oct 2019 01:54:39 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="Psj7J/Xd"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728639AbfJLByi (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 11 Oct 2019 21:54:38 -0400
Received: from mail-pf1-f195.google.com ([209.85.210.195]:44887 "EHLO
        mail-pf1-f195.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726903AbfJLByh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 11 Oct 2019 21:54:37 -0400
Received: by mail-pf1-f195.google.com with SMTP id q21so7069980pfn.11;
        Fri, 11 Oct 2019 18:54:37 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=h6RM8n/hu+J01s3SNVKgH78hp/SMvdzMYgpkm9Vlc0E=;
        b=Psj7J/Xdrx87uLc77BzjrgDpkUPccWetrIkFZW93JzYvCYb1wY3EQIuXyEGQf2XoZ5
         VWbbD3m4zz7iY7EXZ0V7FR6VWXX0N7/EAYwPjdEigFRR52DAc5TWAyxV9lwGBVbRytKQ
         3V+FUTg4NJnpqK0gUR6ti3cklY8zuV+zUnG7Pu7VFmGVMGMpFF6suFUlFpXeUX0c4TC/
         854p0MP4bC1ODOJKqcv5mzDgr/teGKMUJYh39+uA+ui6qebIgvuQBfkCt/3tdo71IW9s
         yAO9mXCT8fx+ZnNeWm0QkFx2cJdB0XzMf2gc3pPSZprP+XCXiT6NKn5t85hoJEuhMi81
         eK5Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=h6RM8n/hu+J01s3SNVKgH78hp/SMvdzMYgpkm9Vlc0E=;
        b=RX7kDauASOESQjJH83QVH6GxtUK1Kwp7BYLviN20ka7btnpRRo1zhnuHIpHjSmCM7c
         LMQzX1Ol/vo4zbdSWf2B/dVzhf9eGdEOWZpbEShLt0aSI/ocZ3PwA0PyH8ykW0NQWTTu
         X7oQWMBwzejviuG19XaknnxWNbsUrhhORIitiALz+o3uVpV248PecCx14sEy1W8wvcCK
         lnVrdu5425a3U1cJsSUTsfelxYw1beqUHpD4vG+Hwjgm0HCY6eAS0fbQoHBsNSthxn+u
         ttMLM8q0711kAZ6Jdf8ilOVDJdDhyPQB8r/a0L56m7iP+BY+xrtYmtcBB9wT4DXXSZTO
         xQCQ==
X-Gm-Message-State: APjAAAVn7OOyO2NvcAdh1MBZTJIxgTvilCF/lvh9DQM7EuMPYw37Sqal
        pcbVKahBfZg1iDgk5Vf17j1L6IgE
X-Google-Smtp-Source: 
 APXvYqwzr4g9BpxV8IvNgAMPr4eoJ3NUv72g45jMas1+qQDBwpTTEv6qQRhPd7yL5zVM1vx636sy9w==
X-Received: by 2002:aa7:956a:: with SMTP id
 x10mr19835260pfq.114.1570845276837;
        Fri, 11 Oct 2019 18:54:36 -0700 (PDT)
Received: from localhost.localdomain (KD124211219252.ppp-bb.dion.ne.jp.
 [124.211.219.252])
        by smtp.gmail.com with ESMTPSA id
 e127sm10992187pfe.37.2019.10.11.18.54.34
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 11 Oct 2019 18:54:36 -0700 (PDT)
From: prashantbhole.linux@gmail.com
To: "Michael S . Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        "David S . Miller" <davem@davemloft.net>
Cc: Prashant Bhole <prashantbhole.linux@gmail.com>,
        David Ahern <dsahern@gmail.com>, kvm@vger.kernel.org,
        netdev@vger.kernel.org
Subject: [PATCH net-next 1/3] tuntap: reorganize tun_msg_ctl usage
Date: Sat, 12 Oct 2019 10:53:55 +0900
Message-Id: <20191012015357.1775-2-prashantbhole.linux@gmail.com>
X-Mailer: git-send-email 2.21.0
In-Reply-To: <20191012015357.1775-1-prashantbhole.linux@gmail.com>
References: <20191012015357.1775-1-prashantbhole.linux@gmail.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Prashant Bhole <prashantbhole.linux@gmail.com>

In order to extend the usage of tun_msg_ctl structure, this patch
changes the member name from type to cmd. Also following definitions
are changed:
TUN_MSG_PTR : TUN_CMD_BATCH
TUN_MSG_UBUF: TUN_CMD_PACKET

Signed-off-by: Prashant Bhole <prashantbhole.linux@gmail.com>
---
 drivers/net/tap.c      | 9 ++++++---
 drivers/net/tun.c      | 8 ++++++--
 drivers/vhost/net.c    | 4 ++--
 include/linux/if_tun.h | 6 +++---
 4 files changed, 17 insertions(+), 10 deletions(-)

```
#### [PATCH RFC v2 1/2] vhost: option to fetch descriptors through an independent struct
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11186947
Return-Path: <SRS0=yg+T=YF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0A214912
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 12 Oct 2019 19:19:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D5EA220679
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 12 Oct 2019 19:19:02 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729821AbfJLTS5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 12 Oct 2019 15:18:57 -0400
Received: from mx1.redhat.com ([209.132.183.28]:51930 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729692AbfJLTS5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 12 Oct 2019 15:18:57 -0400
Received: from mail-qk1-f199.google.com (mail-qk1-f199.google.com
 [209.85.222.199])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 8B55D356C9
        for <kvm@vger.kernel.org>; Sat, 12 Oct 2019 19:18:56 +0000 (UTC)
Received: by mail-qk1-f199.google.com with SMTP id d25so12623667qkk.17
        for <kvm@vger.kernel.org>; Sat, 12 Oct 2019 12:18:56 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:references
         :mime-version:content-disposition:in-reply-to;
        bh=4QQJmzFzcB+s98hCdlFYskwk8yd9+Vjxg/V7InxbF+w=;
        b=uljssza9GX7QPcQo/NuuoScVRhc2mbb4LubG854qR4xwlz6pu7H1B5yGwpSKXvdlPA
         DvN7DMuGWis7LgcYYEgxqZP8jnVqNDmcXbmlR3Bqo4ZFcA5P3JtZPoIyV/5aVl4tUhlV
         Xr0Cx+wHS5zNc5j8Nb9MOkgil4zgpj7z0YMiE56EcKLsNHXMl//1p1lAgDQzRAEz/KPv
         dv9kLfAsPPoFgTPVnHA0o9JzTdCL+S9KsXHD24FX460din7z1+1xdIg342TsfBCBNQ8/
         8GKV6EmTPAN8/MQskZbGTcq0mwQ83nFlLJ2X5yoXx8+4CNLPi8KjvYCvKtG0VeYpxGNX
         boTA==
X-Gm-Message-State: APjAAAUYMwXExs0b4hiTPRXh0CKr1tEsJHQehFOSOVOvQfvgFjGHN4oo
        7xL5wdRAjiNABUXdE5XXEo4ysUYx6VD+mQpoigoD6wtW8E7pA4Brys0iu0BJlvvYD7oln5hM5+e
        NysSYRULC3AoI
X-Received: by 2002:a37:65d0:: with SMTP id
 z199mr21529265qkb.137.1570907935585;
        Sat, 12 Oct 2019 12:18:55 -0700 (PDT)
X-Google-Smtp-Source: 
 APXvYqyT3x3y3mOqhW8zjIYMgyV4Tol+AlDLxT1x66xi6of9QPBAN/ULOCUHzVcDrEbHD57K0CnyUw==
X-Received: by 2002:a37:65d0:: with SMTP id
 z199mr21529232qkb.137.1570907934970;
        Sat, 12 Oct 2019 12:18:54 -0700 (PDT)
Received: from redhat.com (bzq-79-176-10-77.red.bezeqint.net. [79.176.10.77])
        by smtp.gmail.com with ESMTPSA id
 w45sm7611219qtb.47.2019.10.12.12.18.52
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Sat, 12 Oct 2019 12:18:54 -0700 (PDT)
Date: Sat, 12 Oct 2019 15:18:50 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, Jason Wang <jasowang@redhat.com>
Subject: [PATCH RFC v2 1/2] vhost: option to fetch descriptors through an
 independent struct
Message-ID: <20191012191820.8050-2-mst@redhat.com>
References: <20191012191820.8050-1-mst@redhat.com>
MIME-Version: 1.0
Content-Disposition: inline
In-Reply-To: <20191012191820.8050-1-mst@redhat.com>
X-Mailer: git-send-email 2.22.0.678.g13338e74b8
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The idea is to support multiple ring formats by converting
to a format-independent array of descriptors.

This costs extra cycles, but we gain in ability
to fetch a batch of descriptors in one go, which
is good for code cache locality.

To simplify benchmarking, I kept the old code
around so one can switch back and forth by
writing into a module parameter.
This will go away in the final submission.

This patch causes a minor performance degradation,
it's been kept as simple as possible for ease of review.
Next patch gets us back the performance by adding batching.

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>
---
 drivers/vhost/test.c  |  17 ++-
 drivers/vhost/vhost.c | 299 +++++++++++++++++++++++++++++++++++++++++-
 drivers/vhost/vhost.h |  16 +++
 3 files changed, 327 insertions(+), 5 deletions(-)

```
