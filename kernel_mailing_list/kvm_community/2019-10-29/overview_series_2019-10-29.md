#### [PATCH 1/4] kvm: nested: Introduce read_and_check_msr_entry()From: Aaron Lewis <aaronlewis@google.com>
##### From: Aaron Lewis <aaronlewis@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Aaron Lewis <aaronlewis@google.com>
X-Patchwork-Id: 11218549
Return-Path: <SRS0=zizX=YW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6F10A13BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 29 Oct 2019 21:06:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4B63F21721
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 29 Oct 2019 21:06:14 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="dnwnfKnb"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728339AbfJ2VGN (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 29 Oct 2019 17:06:13 -0400
Received: from mail-pf1-f201.google.com ([209.85.210.201]:50580 "EHLO
        mail-pf1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725840AbfJ2VGN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 29 Oct 2019 17:06:13 -0400
Received: by mail-pf1-f201.google.com with SMTP id y191so12370959pfg.17
        for <kvm@vger.kernel.org>; Tue, 29 Oct 2019 14:06:11 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=W9TmDvzIpvVvMh9ub0E4eq3Yi9eArcf8ZO+zuv8WQrQ=;
        b=dnwnfKnb9LznXfooKlHBCD3nDnHj7i29u4P50wfU8RS1Z6IcHtJL8+pyAO0+NzVNPz
         h1C3ez6pqwVDSJiuIOaHvDOBXRw6MwohdqK96V7KrL3IeIERwx6OifF0bLo2D+1//iey
         viubex1XFg6kK3g1F0/uD3w8mSfnu95jJrxB3Jv+75njyRG2GKF/uaTDqGP/gs3U/3PL
         aCBtxIOtnmgiNZmxmjvFZ1h4At8bH3LI3+E81V5+/ZknVsZS60uy8sPsoyohjnG8kmqv
         EwPmH0o6LlQZc8JpVQJBMx2d5u/Yusw+cMXvjRG66qWtIBIRFv5pig09bIQ0Ay7P2nLm
         Y3Cw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=W9TmDvzIpvVvMh9ub0E4eq3Yi9eArcf8ZO+zuv8WQrQ=;
        b=LrQj8sskM5f6x/EZAmsS4sg9Ctx4V3Ap20GbJq6ngWCAYoZ+LHO3YlCLRTCVULlJdW
         g9+YEOHCcfsYqYE0q/CZ7JtEtwTEWpUAhzIvW+NQlMg/uRytzySwVMqUXzdz+KyGRVE5
         xX3nnxFszXmVTQiMUCWrIhxfTCqPADwta2ZRNCWimbYnN00egqsyML3O6bg2agrX0QPc
         t5d+Eoh+lvBzPoI9T49J+St5SGN9FCHqXci2+Spa9iGruwYEh0870n1vKj3DOVS3NR/s
         f2YrS5ejjtfH8LKUI0iKPlmOAKjOQbJ5YR3QsoaCwH4Ll0sLTcv5pNQTR9dHMuVE8FXX
         tBgg==
X-Gm-Message-State: APjAAAVluBEpnHgUr+kD2ePt9tT95LwF8O/qM0M/Kkh6MWU/22wUyAOR
        UuTz0pl/l3ZRFh0BNUt2TiifS5zqqbHRE4Hiu8ACjyBuLeks+UtN+sVYK6hNZ5LZMqiqV0HZDXf
        oHC3QKO/bMhEN4sUYfc5lidyFBb7pzDCyRl7QCzoH8eimb8+o/Ka/9dMOYKXgtIoHh2p7
X-Google-Smtp-Source: 
 APXvYqw6qwdYZn2QAO9KRRcHT9+jwhmrkdZyYbz/rpIZlb5i3BWHg+po/FEv5+Zk74fdNg3wFoe5xrOWH4x+w8KG
X-Received: by 2002:a63:4a50:: with SMTP id
 j16mr26630256pgl.308.1572383170907;
 Tue, 29 Oct 2019 14:06:10 -0700 (PDT)
Date: Tue, 29 Oct 2019 14:05:52 -0700
In-Reply-To: <20191029210555.138393-1-aaronlewis@google.com>
Message-Id: <20191029210555.138393-2-aaronlewis@google.com>
Mime-Version: 1.0
References: <20191029210555.138393-1-aaronlewis@google.com>
X-Mailer: git-send-email 2.24.0.rc0.303.g954a862665-goog
Subject: [PATCH 1/4] kvm: nested: Introduce read_and_check_msr_entry()
From: Aaron Lewis <aaronlewis@google.com>
To: kvm@vger.kernel.org
Cc: Aaron Lewis <aaronlewis@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add the function read_and_check_msr_entry() which just pulls some code
out of nested_vmx_store_msr() for now, however, this is in preparation
for a change later in this series were we reuse the code in
read_and_check_msr_entry().

Signed-off-by: Aaron Lewis <aaronlewis@google.com>
Change-Id: Iaf8787198c06674e8b0555982a962f5bd288e43f
---
 arch/x86/kvm/vmx/nested.c | 35 ++++++++++++++++++++++-------------
 1 file changed, 22 insertions(+), 13 deletions(-)

```
#### [PATCH] arch: x86: kvm: mmu.c: use true/false for bool type
##### From: Saurav Girepunje <saurav.girepunje@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Saurav Girepunje <saurav.girepunje@gmail.com>
X-Patchwork-Id: 11217509
Return-Path: <SRS0=zizX=YW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7ECD41515
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 29 Oct 2019 09:41:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5B92E214B2
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 29 Oct 2019 09:41:18 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="j9criezC"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732697AbfJ2JlO (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 29 Oct 2019 05:41:14 -0400
Received: from mail-pf1-f196.google.com ([209.85.210.196]:35376 "EHLO
        mail-pf1-f196.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728575AbfJ2JlO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 29 Oct 2019 05:41:14 -0400
Received: by mail-pf1-f196.google.com with SMTP id d13so8095941pfq.2;
        Tue, 29 Oct 2019 02:41:13 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=date:from:to:cc:subject:message-id:mime-version:content-disposition
         :user-agent;
        bh=CAwKwW00jVJm51PG91lfRY/TjBZMpZIpgU/Tpy8p9zA=;
        b=j9criezCX7eU0jJjWFTxMlc2b+idSvhrzjxVluwqNar9ukM81im9ZVYrPuM8JcGaPV
         X3fHe7ZsPocJiki6ovRutrBu/PFxi257dA2t9gIz7bUxkWX0VLtscV8pLt7rpI7d2sX3
         6wM6Sy8fPpIDQwhXgvqz6FBB8W/1+U03argQsOO3H3Tg1jM3hX212sN5GJOwbtyUZ/jt
         clkcw/lrbfiz9xwE5JiAYjK5CUEzC/UA51JwZjUYPCCE5/OYsq5P5YKzPOJ2wxGwt3d8
         t9UncDYXCkJXkGphbT2+cjxYsvlh1lou5Xtrkik0/1WUnkWhbjdIczBdwBicfoM0NUtl
         arCw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition:user-agent;
        bh=CAwKwW00jVJm51PG91lfRY/TjBZMpZIpgU/Tpy8p9zA=;
        b=bVps3cnUJhR+QnrTT2I4v3LSTI1i4PCmOB7Jz+jwnhNfU1IA3SdZso+ot80t19DLCa
         H87zp9kTO92MUlybjTmA7TUtztWqThete4lfzLi2kzcJdGPZwRgDZyDfIeTi3mAyx48x
         beWZVCBf+rqGV6xgVMqVVxXBfghXD5DxRHVq/R72a+SX5qwIjLiYKnwjqgNIwb1xgaBX
         bmoTxXBQp6hvzI0K/LHJDjWh0M7a/wYj48SYfzTVF+0NI0d7fgu+YlFGY1n1oPQ3tDF/
         sNIQtQM/Hh8SoPpGfqwadQm5SVZ4I6135arX7qK2s81IO4/Zcc+JBVpRo4h7+EIpTcYq
         sbMQ==
X-Gm-Message-State: APjAAAULJhS+ND+vNUDv0o8WO4S/fp9f5dNrDjvwIe399iVJbR0gXGOx
        MqFnZnSVym/iuBnAbXyEucKsHArkwe8=
X-Google-Smtp-Source: 
 APXvYqw86yuRdfHlvx/v3GOZgKl4ljAECR5j49//D1MsdQt1P0dDSM3APydSUDfp9PJvAghARaHOXQ==
X-Received: by 2002:a17:90a:17ad:: with SMTP id
 q42mr5375829pja.100.1572342073174;
        Tue, 29 Oct 2019 02:41:13 -0700 (PDT)
Received: from saurav ([27.62.167.137])
        by smtp.gmail.com with ESMTPSA id
 q3sm16251023pgj.54.2019.10.29.02.41.07
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 29 Oct 2019 02:41:12 -0700 (PDT)
Date: Tue, 29 Oct 2019 15:11:04 +0530
From: Saurav Girepunje <saurav.girepunje@gmail.com>
To: pbonzini@redhat.com, rkrcmar@redhat.com,
        sean.j.christopherson@intel.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        tglx@linutronix.de, mingo@redhat.com, bp@alien8.de, hpa@zytor.com,
        x86@kernel.org, kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: saurav.girepunje@hotmail.com
Subject: [PATCH] arch: x86: kvm: mmu.c: use true/false for bool type
Message-ID: <20191029094104.GA11220@saurav>
MIME-Version: 1.0
Content-Disposition: inline
User-Agent: Mutt/1.10.1 (2018-07-13)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Use true/false for bool type "dbg" in mmu.c

Signed-off-by: Saurav Girepunje <saurav.girepunje@gmail.com>
---
 arch/x86/kvm/mmu.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v3 1/3] kcov: remote coverage supportFrom: Andrey Konovalov <andreyknvl@google.com>
##### From: Andrey Konovalov <andreyknvl@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrey Konovalov <andreyknvl@google.com>
X-Patchwork-Id: 11218141
Return-Path: <SRS0=zizX=YW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 025331390
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 29 Oct 2019 16:32:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id AEAC021721
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 29 Oct 2019 16:32:48 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="bN568Qkz"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2390485AbfJ2Qcp (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 29 Oct 2019 12:32:45 -0400
Received: from mail-ua1-f74.google.com ([209.85.222.74]:39624 "EHLO
        mail-ua1-f74.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2390409AbfJ2Qco (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 29 Oct 2019 12:32:44 -0400
Received: by mail-ua1-f74.google.com with SMTP id b5so2359460uap.6
        for <kvm@vger.kernel.org>; Tue, 29 Oct 2019 09:32:41 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=eVNoIfefZ+XIoQSZe2yFMglEi3qqcrN7/R3rTPwzE2k=;
        b=bN568Qkzf9cfzBXGM0tzsRgQ0Lx3EdYzqb1jAt0Bn1//E0V8lDm75XaiuDu2i+Hldk
         r8WeUBTo6fLMAmljFjSiz4hLBsYJMKOfbFUqKinDA+EUy7s3jVEei/BnbHbaK4wddxGD
         vPTxypai6ZkkFjtEIRXMTXdBIRY++o22ms0aqaHBVNNfPAmvZCTSe1egkfkQWaAw3yI4
         JZvlhVV0WPBlAzm3YEc+Jp4l9RUNK01wTQ2NbNjOAoHytNireHNyGchfJWjao5W+u3T+
         l4MYlenB7GZ4BfgSrHvYVfKn7Dsvsa0+j5y1OJ4wX02oRWN3Sau7ojc5aiOdMzsWXjCQ
         arIQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=eVNoIfefZ+XIoQSZe2yFMglEi3qqcrN7/R3rTPwzE2k=;
        b=ruJ7Miq/r5z689SvGaMP8bP7cOQ28u/eLG9Ph1SWIP7vcclotK0kh7/lfnim0bWAMy
         S7//wPtVRzrhTRgPGWLBXun9mhwe8DJDQs/cnR+XZv7+nHU/uCBZIubWYiVkIheLYG8G
         df4luKjp8153aG6p5KdH8FzXIJY7g2nexBJYxX2O/naj2tqbSQnuB9DYDm+8CP4R9uRp
         0iMELVXYajAlj+N4l2O46KKzNFDMsMMUIYP+jDuaj8qOhwTUbx95JnvaWK27Uhwn6Dmg
         4x9ab4cFKY6EssK0z4AIZ3HqLz1O/w0utDyPkBOKglEnJmwvoClL8hwajFIc6C9hiJUV
         hxpA==
X-Gm-Message-State: APjAAAUujVk/yxrkZSuKPVrVVdhcQTM2VYTt48x45UEWhmvPbRxUoBfV
        /j1ruF/vwEP+QEGYVpZTJ5oiyFubDGOPyD+o
X-Google-Smtp-Source: 
 APXvYqz7uHV7QPNVpBBr7eWN1kOIqnVZm7Ex5hn2qm9xh3RoXWFoM0j2ut6rUXwCUkdWdzZ2mSz8bfva7folKVuF
X-Received: by 2002:a1f:5c94:: with SMTP id
 q142mr12039540vkb.85.1572366760456;
 Tue, 29 Oct 2019 09:32:40 -0700 (PDT)
Date: Tue, 29 Oct 2019 17:32:27 +0100
In-Reply-To: <cover.1572366574.git.andreyknvl@google.com>
Message-Id: 
 <e90e315426a384207edbec1d6aa89e43008e4caf.1572366574.git.andreyknvl@google.com>
Mime-Version: 1.0
References: <cover.1572366574.git.andreyknvl@google.com>
X-Mailer: git-send-email 2.24.0.rc0.303.g954a862665-goog
Subject: [PATCH v3 1/3] kcov: remote coverage support
From: Andrey Konovalov <andreyknvl@google.com>
To: linux-usb@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        linux-kernel@vger.kernel.org, Dmitry Vyukov <dvyukov@google.com>,
        Greg Kroah-Hartman <gregkh@linuxfoundation.org>,
        Alan Stern <stern@rowland.harvard.edu>,
        "Michael S . Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>
Cc: Andrew Morton <akpm@linux-foundation.org>,
        Arnd Bergmann <arnd@arndb.de>,
        Steven Rostedt <rostedt@goodmis.org>,
        David Windsor <dwindsor@gmail.com>,
        Elena Reshetova <elena.reshetova@intel.com>,
        Anders Roxell <anders.roxell@linaro.org>,
        Alexander Potapenko <glider@google.com>,
        Marco Elver <elver@google.com>,
        Andrey Konovalov <andreyknvl@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch adds background thread coverage collection ability to kcov.

With KCOV_ENABLE coverage is collected only for syscalls that are issued
from the current process. With KCOV_REMOTE_ENABLE it's possible to collect
coverage for arbitrary parts of the kernel code, provided that those parts
are annotated with kcov_remote_start()/kcov_remote_stop().

This allows to collect coverage from two types of kernel background
threads: the global ones, that are spawned during kernel boot in a limited
number of instances (e.g. one USB hub_event() worker thread is spawned per
USB HCD); and the local ones, that are spawned when a user interacts with
some kernel interface (e.g. vhost workers).

To enable collecting coverage from a global background thread, a unique
global handle must be assigned and passed to the corresponding
kcov_remote_start() call. Then a userspace process can pass a list of such
handles to the KCOV_REMOTE_ENABLE ioctl in the handles array field of the
kcov_remote_arg struct. This will attach the used kcov device to the code
sections, that are referenced by those handles.

Since there might be many local background threads spawned from different
userspace processes, we can't use a single global handle per annotation.
Instead, the userspace process passes a non-zero handle through the
common_handle field of the kcov_remote_arg struct. This common handle gets
saved to the kcov_handle field in the current task_struct and needs to be
passed to the newly spawned threads via custom annotations. Those threads
should in turn be annotated with kcov_remote_start()/kcov_remote_stop().

Internally kcov stores handles as u64 integers. The top byte of a handle
is used to denote the id of a subsystem that this handle belongs to, and
the lower 4 bytes are used to denote the id of a thread instance within
that subsystem. A reserved value 0 is used as a subsystem id for common
handles as they don't belong to a particular subsystem. The bytes 4-7 are
currently reserved and must be zero. In the future the number of bytes
used for the subsystem or handle ids might be increased.

When a particular userspace proccess collects coverage by via a common
handle, kcov will collect coverage for each code section that is annotated
to use the common handle obtained as kcov_handle from the current
task_struct. However non common handles allow to collect coverage
selectively from different subsystems.

Signed-off-by: Andrey Konovalov <andreyknvl@google.com>
---
 Documentation/dev-tools/kcov.rst | 129 ++++++++
 include/linux/kcov.h             |  23 ++
 include/linux/sched.h            |   8 +
 include/uapi/linux/kcov.h        |  28 ++
 kernel/kcov.c                    | 547 +++++++++++++++++++++++++++++--
 5 files changed, 700 insertions(+), 35 deletions(-)

```
#### [RFC] vhost_mdev: add network control vq support
##### From: Tiwei Bie <tiwei.bie@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tiwei Bie <tiwei.bie@intel.com>
X-Patchwork-Id: 11217565
Return-Path: <SRS0=zizX=YW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 39BEF139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 29 Oct 2019 10:17:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 21866208E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 29 Oct 2019 10:17:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730298AbfJ2KRA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 29 Oct 2019 06:17:00 -0400
Received: from mga17.intel.com ([192.55.52.151]:33370 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728868AbfJ2KRA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 29 Oct 2019 06:17:00 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga001.jf.intel.com ([10.7.209.18])
  by fmsmga107.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 29 Oct 2019 03:16:59 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.68,243,1569308400";
   d="scan'208";a="283199335"
Received: from dpdk-virtio-tbie-2.sh.intel.com ([10.67.104.74])
  by orsmga001.jf.intel.com with ESMTP; 29 Oct 2019 03:16:57 -0700
From: Tiwei Bie <tiwei.bie@intel.com>
To: mst@redhat.com, jasowang@redhat.com
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        dan.daly@intel.com, cunming.liang@intel.com,
        zhihong.wang@intel.com, lingshan.zhu@intel.com, tiwei.bie@intel.com
Subject: [RFC] vhost_mdev: add network control vq support
Date: Tue, 29 Oct 2019 18:17:26 +0800
Message-Id: <20191029101726.12699-1-tiwei.bie@intel.com>
X-Mailer: git-send-email 2.23.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch adds the network control vq support in vhost-mdev.
A vhost-mdev specific op is introduced to allow parent drivers
to handle the network control commands come from userspace.

Signed-off-by: Tiwei Bie <tiwei.bie@intel.com>
---
This patch depends on below patch:
https://lkml.org/lkml/2019/10/29/335

 drivers/vhost/mdev.c             | 37 ++++++++++++++++++++++++++++++--
 include/linux/virtio_mdev_ops.h  | 10 +++++++++
 include/uapi/linux/vhost.h       |  7 ++++++
 include/uapi/linux/vhost_types.h |  6 ++++++
 4 files changed, 58 insertions(+), 2 deletions(-)

```
#### [PATCH] s390: vfio-ap: disable IRQ in remove callback results in kernel OOPS
##### From: Tony Krowiak <akrowiak@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tony Krowiak <akrowiak@linux.ibm.com>
X-Patchwork-Id: 11218695
Return-Path: <SRS0=zizX=YW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 715C815AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 29 Oct 2019 22:09:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4F4AA217F9
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 29 Oct 2019 22:09:18 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727181AbfJ2WJO (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 29 Oct 2019 18:09:14 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:14488 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725867AbfJ2WJO (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 29 Oct 2019 18:09:14 -0400
Received: from pps.filterd (m0098394.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x9TM37IZ068340;
        Tue, 29 Oct 2019 18:09:13 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2vxwnegg0p-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 29 Oct 2019 18:09:13 -0400
Received: from m0098394.ppops.net (m0098394.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.27/8.16.0.27) with SMTP id x9TM7n0b108292;
        Tue, 29 Oct 2019 18:09:12 -0400
Received: from ppma05wdc.us.ibm.com (1b.90.2fa9.ip4.static.sl-reverse.com
 [169.47.144.27])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2vxwnegg08-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 29 Oct 2019 18:09:12 -0400
Received: from pps.filterd (ppma05wdc.us.ibm.com [127.0.0.1])
        by ppma05wdc.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 x9TM8YAE009965;
        Tue, 29 Oct 2019 22:09:11 GMT
Received: from b01cxnp23034.gho.pok.ibm.com (b01cxnp23034.gho.pok.ibm.com
 [9.57.198.29])
        by ppma05wdc.us.ibm.com with ESMTP id 2vxwh5r5vm-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 29 Oct 2019 22:09:11 +0000
Received: from b01ledav005.gho.pok.ibm.com (b01ledav005.gho.pok.ibm.com
 [9.57.199.110])
        by b01cxnp23034.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id x9TM99SQ33620394
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 29 Oct 2019 22:09:09 GMT
Received: from b01ledav005.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id A6CBEAE48A;
        Tue, 29 Oct 2019 22:09:09 +0000 (GMT)
Received: from b01ledav005.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 6334EAE487;
        Tue, 29 Oct 2019 22:09:09 +0000 (GMT)
Received: from akrowiak-ThinkPad-P50.endicott.ibm.com (unknown [9.60.75.238])
        by b01ledav005.gho.pok.ibm.com (Postfix) with ESMTPS;
        Tue, 29 Oct 2019 22:09:09 +0000 (GMT)
From: Tony Krowiak <akrowiak@linux.ibm.com>
To: linux-s390@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org
Cc: heiko.carstens@de.ibm.com, gor@linux.ibm.com,
        borntraeger@de.ibm.com, freude@linux.ibm.com, cohuck@redhat.com,
        mjrosato@linux.ibm.com, pmorel@linux.ibm.com, pasic@linux.ibm.com,
        jjherne@linux.ibm.com, aekrowia <akrowiak@linux.ibm.com>
Subject: [PATCH] s390: vfio-ap: disable IRQ in remove callback results in
 kernel OOPS
Date: Tue, 29 Oct 2019 18:09:06 -0400
Message-Id: <1572386946-22566-1-git-send-email-akrowiak@linux.ibm.com>
X-Mailer: git-send-email 2.7.4
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-10-29_06:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=0 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=999 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1908290000 definitions=main-1910290190
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: aekrowia <akrowiak@linux.ibm.com>

When an AP adapter card is configured off via the SE or the SCLP
Deconfigure Adjunct Processor command and the AP bus subsequently detects
that the adapter card is no longer in the AP configuration, the card
device representing the adapter card as well as each of its associated
AP queue devices will be removed by the AP bus. If one or more of the
affected queue devices is bound to the VFIO AP device driver, its remove
callback will be invoked for each queue to be removed. The remove callback
resets the queue and disables IRQ processing. If interrupt processing was
never enabled for the queue, disabling IRQ processing will fail resulting
in a kernel OOPS.

This patch verifies IRQ processing is enabled before attempting to disable
interrupts for the queue.

Signed-off-by: Tony Krowiak <akrowiak@linux.ibm.com>
Signed-off-by: aekrowia <akrowiak@linux.ibm.com>
---
 drivers/s390/crypto/vfio_ap_drv.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH v3] vhost: introduce mdev based hardware backend
##### From: Tiwei Bie <tiwei.bie@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tiwei Bie <tiwei.bie@intel.com>
X-Patchwork-Id: 11217551
Return-Path: <SRS0=zizX=YW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 46C62112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 29 Oct 2019 10:06:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 10E782087F
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 29 Oct 2019 10:06:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728361AbfJ2KGv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 29 Oct 2019 06:06:51 -0400
Received: from mga07.intel.com ([134.134.136.100]:61266 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727578AbfJ2KGv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 29 Oct 2019 06:06:51 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga007.jf.intel.com ([10.7.209.58])
  by orsmga105.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 29 Oct 2019 03:06:50 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.68,243,1569308400";
   d="scan'208";a="189894140"
Received: from dpdk-virtio-tbie-2.sh.intel.com ([10.67.104.74])
  by orsmga007.jf.intel.com with ESMTP; 29 Oct 2019 03:06:47 -0700
From: Tiwei Bie <tiwei.bie@intel.com>
To: mst@redhat.com, jasowang@redhat.com, alex.williamson@redhat.com,
        maxime.coquelin@redhat.com
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        dan.daly@intel.com, cunming.liang@intel.com,
        zhihong.wang@intel.com, lingshan.zhu@intel.com, tiwei.bie@intel.com
Subject: [PATCH v3] vhost: introduce mdev based hardware backend
Date: Tue, 29 Oct 2019 18:07:34 +0800
Message-Id: <20191029100734.9861-1-tiwei.bie@intel.com>
X-Mailer: git-send-email 2.23.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch introduces a mdev based hardware vhost backend.
This backend is built on top of the same abstraction used
in virtio-mdev and provides a generic vhost interface for
userspace to accelerate the virtio devices in guest.

This backend is implemented as a mdev device driver on top
of the same mdev device ops used in virtio-mdev but using
a different mdev class id, and it will register the device
as a VFIO device for userspace to use. Userspace can setup
the IOMMU with the existing VFIO container/group APIs and
then get the device fd with the device name. After getting
the device fd of this device, userspace can use vhost ioctls
to setup the backend.

Signed-off-by: Tiwei Bie <tiwei.bie@intel.com>
---
This patch depends on below series:
https://lkml.org/lkml/2019/10/23/614

v2 -> v3:
- Fix the return value (Jason);
- Don't cache unnecessary information in vhost-mdev (Jason);
- Get rid of the memset in open (Jason);
- Add comments for VHOST_SET_MEM_TABLE, ... (Jason);
- Filter out unsupported features in vhost-mdev (Jason);
- Add _GET_DEVICE_ID ioctl (Jason);
- Add _GET_CONFIG/_SET_CONFIG ioctls (Jason);
- Drop _GET_QUEUE_NUM ioctl (Jason);
- Fix the copy-paste errors in _IOW/_IOR usage;
- Some minor fixes and improvements;

v1 -> v2:
- Replace _SET_STATE with _SET_STATUS (MST);
- Check status bits at each step (MST);
- Report the max ring size and max number of queues (MST);
- Add missing MODULE_DEVICE_TABLE (Jason);
- Only support the network backend w/o multiqueue for now;
- Some minor fixes and improvements;
- Rebase on top of virtio-mdev series v4;

RFC v4 -> v1:
- Implement vhost-mdev as a mdev device driver directly and
  connect it to VFIO container/group. (Jason);
- Pass ring addresses as GPAs/IOVAs in vhost-mdev to avoid
  meaningless HVA->GPA translations (Jason);

RFC v3 -> RFC v4:
- Build vhost-mdev on top of the same abstraction used by
  virtio-mdev (Jason);
- Introduce vhost fd and pass VFIO fd via SET_BACKEND ioctl (MST);

RFC v2 -> RFC v3:
- Reuse vhost's ioctls instead of inventing a VFIO regions/irqs
  based vhost protocol on top of vfio-mdev (Jason);

RFC v1 -> RFC v2:
- Introduce a new VFIO device type to build a vhost protocol
  on top of vfio-mdev;

 drivers/vfio/mdev/mdev_core.c    |  20 ++
 drivers/vfio/mdev/mdev_private.h |   1 +
 drivers/vhost/Kconfig            |  12 +
 drivers/vhost/Makefile           |   3 +
 drivers/vhost/mdev.c             | 554 +++++++++++++++++++++++++++++++
 include/linux/mdev.h             |   5 +
 include/uapi/linux/vhost.h       |  18 +
 include/uapi/linux/vhost_types.h |   8 +
 8 files changed, 621 insertions(+)
 create mode 100644 drivers/vhost/mdev.c

```
