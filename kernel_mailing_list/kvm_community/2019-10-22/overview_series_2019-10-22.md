#### [PATCH v12 QEMU 2/3] virtio-balloon: Add bit to notify guest of unused page reporting
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11205435
Return-Path: <SRS0=lBCn=YP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9563413BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Oct 2019 22:29:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 72F1A20684
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Oct 2019 22:29:37 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="ub96VsE/"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389299AbfJVW3d (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 22 Oct 2019 18:29:33 -0400
Received: from mail-pf1-f194.google.com ([209.85.210.194]:41154 "EHLO
        mail-pf1-f194.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1731376AbfJVW3d (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 22 Oct 2019 18:29:33 -0400
Received: by mail-pf1-f194.google.com with SMTP id q7so11533198pfh.8;
        Tue, 22 Oct 2019 15:29:33 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:in-reply-to:references
         :user-agent:mime-version:content-transfer-encoding;
        bh=VitjQQFQG7H0A5JYqbYhHy/YWDiYO6QESupJyX3H62U=;
        b=ub96VsE/aHpg9djCBphz/P7fdVY3n86o/XWb1FAYTGbSu3AwR4K9lBGmtTy/Wn7cq8
         pKmFbjXvCiAO/AnmPTA2xqH9ItqQ0QHW1e9m+fpikl/zoHAGuewJtMT+qYpkYU4d+sNB
         bRcwsxXm9qsjO4pPJRl9GrFQmmL7vyQVSjyqte3AigLrzhUm2sgR2QhetUXUFq1lw6Ms
         qK4rAZkMI7fL6gZSq06ke+W7yIVRWBRusrfPAujAVqlWXkE/ORuUZRRSsb/pqEPLL9kS
         4niZNMgMERqwHAwhWTfqEOfuvdAYHH2aBZ8LE+reCLeCfFrdukQ02pYjZs0F/UIQzwSa
         +3pA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:in-reply-to
         :references:user-agent:mime-version:content-transfer-encoding;
        bh=VitjQQFQG7H0A5JYqbYhHy/YWDiYO6QESupJyX3H62U=;
        b=UzGM2dm3c07vimaWiyna6p69GopwNrdp5Q8tX5QOEp7cJ1ko5n1zX+lTO47APIU3JP
         lGE06AUPX0QOX23mwViogiyLD+Kz1SphRml1Xgia1qLLv+Mo5FFSO54CL62djs/+9lvm
         Scj2p5Q/kerkqlIyctBIpIcCjwixgzISmy8u+IxUtC0xA9DtMRFE1alntPEGUMI6eW21
         iG/LwLjREJ0OQleA8qEnyCqYv1fckrf5JL7jCDC1wel7T3ZR1Qglf0oXCSW8GKyctA8P
         fPoMv9PFl4pix/Gde2EEjvxEDSr/FqZjRV8XN5Q5rQzh7saxR4cXvkjojiKS7qNjVin8
         2Ymg==
X-Gm-Message-State: APjAAAUcBCNfULgW4//UwazZhOOkGFFhWJ49sYXjSmecS9k0a0lQMU1B
        qeU9HJtRY5AAh0+oGdhSQLA=
X-Google-Smtp-Source: 
 APXvYqzOM4u5GmGbN/ocrgEqoziD4wWkt1Nwwr1fbqvYRLXfjz4D1ifewFxxUB9G7yy1bBtSvW1EJg==
X-Received: by 2002:a17:90a:b902:: with SMTP id
 p2mr7613515pjr.62.1571783372563;
        Tue, 22 Oct 2019 15:29:32 -0700 (PDT)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 f89sm18661852pje.20.2019.10.22.15.29.31
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 22 Oct 2019 15:29:32 -0700 (PDT)
Subject: [PATCH v12 QEMU 2/3] virtio-balloon: Add bit to notify guest of
 unused page reporting
From: Alexander Duyck <alexander.duyck@gmail.com>
To: kvm@vger.kernel.org, mst@redhat.com, linux-kernel@vger.kernel.org,
        willy@infradead.org, mhocko@kernel.org, linux-mm@kvack.org,
        akpm@linux-foundation.org, mgorman@techsingularity.net,
        vbabka@suse.cz
Cc: yang.zhang.wz@gmail.com, nitesh@redhat.com, konrad.wilk@oracle.com,
        david@redhat.com, pagupta@redhat.com, riel@surriel.com,
        lcapitulino@redhat.com, dave.hansen@intel.com,
        wei.w.wang@intel.com, aarcange@redhat.com, pbonzini@redhat.com,
        dan.j.williams@intel.com, alexander.h.duyck@linux.intel.com,
        osalvador@suse.de
Date: Tue, 22 Oct 2019 15:29:31 -0700
Message-ID: <20191022222931.17594.85842.stgit@localhost.localdomain>
In-Reply-To: <20191022221223.17338.5860.stgit@localhost.localdomain>
References: <20191022221223.17338.5860.stgit@localhost.localdomain>
User-Agent: StGit/0.17.1-dirty
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Alexander Duyck <alexander.h.duyck@linux.intel.com>

Add a bit for the page reporting feature provided by virtio-balloon.

This patch should be replaced once the feature is added to the Linux kernel
and the bit is backported into this exported kernel header.

Signed-off-by: Alexander Duyck <alexander.h.duyck@linux.intel.com>
---
 include/standard-headers/linux/virtio_balloon.h |    1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH v12 QEMU 3/3] virtio-balloon: Provide a interface for unused page reporting
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11205439
Return-Path: <SRS0=lBCn=YP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4013E13BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Oct 2019 22:29:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 15E8F218AE
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Oct 2019 22:29:44 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="iKFrq92y"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389371AbfJVW3k (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 22 Oct 2019 18:29:40 -0400
Received: from mail-pg1-f194.google.com ([209.85.215.194]:46703 "EHLO
        mail-pg1-f194.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1731220AbfJVW3j (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 22 Oct 2019 18:29:39 -0400
Received: by mail-pg1-f194.google.com with SMTP id e15so10798401pgu.13;
        Tue, 22 Oct 2019 15:29:39 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:in-reply-to:references
         :user-agent:mime-version:content-transfer-encoding;
        bh=IYnIZF3ya8GRMyw0Z8v44wRFjachYcZ/Qaw0Oz7Yqys=;
        b=iKFrq92yC0OttYiOPOr/01Xrnyzk4LoPd7Kcq49VUCN6eCevIwwnzOhDsuG7WKAr8O
         r/tdirFVwlmIF4XVYxJFp8SMy32fgK5tLn8fTB3UFfxB/f/ERF5gnBU0unC7O+CBNIaG
         tH/jGGoZpWYS3TUu0CBrAfDgx38RUWQa8YNRUFfb+XQZm2LuLisSnddhJdwMYa+hRLmi
         FG51Yo0v/rEZdthSazebVEJha9R7TzUojsB7wi/epBbyrsC21X825kMkvtdovDrYcAPU
         AkTswIZmv7maSnB0W+OsWy0E7hHp/Qc7EHAMeBROhHub00ymWR/lHhP7F1vKpuzss+SG
         pIVQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:in-reply-to
         :references:user-agent:mime-version:content-transfer-encoding;
        bh=IYnIZF3ya8GRMyw0Z8v44wRFjachYcZ/Qaw0Oz7Yqys=;
        b=Yjq2JfBU9ZOjMtk/LOExbLGNNFPWL1PgdsGj+kJYRrEB34XcCzWsG8x668/jtvozc7
         laZ324v/becppJXKqIIpNTI38MC0yf8Wx1ULiSZ701PyGj6jVg6QHWgxQJ3FiTtnXUlb
         8+ubUBZ/idgA8qHVgEXXpYQ6MBLYsOfPhoaB2wdrKZPskwC/tC2KDcoduIjXBZyK06uT
         LJRNJ6k2BBOocyx06WETzvFamMU+DagtesVMpkmseDHE/wTTp3uCU5vMyHJaWJL9i3Ud
         1DmFaH3Fb+czSUYmPgVG3i6MwPLoSh2rvgUukIRKf9jkteeon1cmxSKeL3NeUz87u/v3
         pztg==
X-Gm-Message-State: APjAAAUIx1kaMpY63hy/1eYGzH7TK8HmmGtkDEGVCVb0oOCaJRq4hASZ
        pfLltarGuJtgwgvqqqKTEcE=
X-Google-Smtp-Source: 
 APXvYqxYOPYId/zCW4hr+ch1HRgSCj3NHWSShCU2POCjbAJhcHE4hlH9edmKaMVP7+uqCPxzCvmVBA==
X-Received: by 2002:a65:4bc3:: with SMTP id p3mr6338350pgr.188.1571783378951;
        Tue, 22 Oct 2019 15:29:38 -0700 (PDT)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 o123sm7482309pfg.161.2019.10.22.15.29.37
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 22 Oct 2019 15:29:38 -0700 (PDT)
Subject: [PATCH v12 QEMU 3/3] virtio-balloon: Provide a interface for unused
 page reporting
From: Alexander Duyck <alexander.duyck@gmail.com>
To: kvm@vger.kernel.org, mst@redhat.com, linux-kernel@vger.kernel.org,
        willy@infradead.org, mhocko@kernel.org, linux-mm@kvack.org,
        akpm@linux-foundation.org, mgorman@techsingularity.net,
        vbabka@suse.cz
Cc: yang.zhang.wz@gmail.com, nitesh@redhat.com, konrad.wilk@oracle.com,
        david@redhat.com, pagupta@redhat.com, riel@surriel.com,
        lcapitulino@redhat.com, dave.hansen@intel.com,
        wei.w.wang@intel.com, aarcange@redhat.com, pbonzini@redhat.com,
        dan.j.williams@intel.com, alexander.h.duyck@linux.intel.com,
        osalvador@suse.de
Date: Tue, 22 Oct 2019 15:29:37 -0700
Message-ID: <20191022222937.17594.71516.stgit@localhost.localdomain>
In-Reply-To: <20191022221223.17338.5860.stgit@localhost.localdomain>
References: <20191022221223.17338.5860.stgit@localhost.localdomain>
User-Agent: StGit/0.17.1-dirty
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Alexander Duyck <alexander.h.duyck@linux.intel.com>

Add support for what I am referring to as "unused page reporting".
Basically the idea is to function very similar to how the balloon works
in that we basically end up madvising the page as not being used. However
we don't really need to bother with any deflate type logic since the page
will be faulted back into the guest when it is read or written to.

This is meant to be a simplification of the existing balloon interface
to use for providing hints to what memory needs to be freed. I am assuming
this is safe to do as the deflate logic does not actually appear to do very
much other than tracking what subpages have been released and which ones
haven't.

Signed-off-by: Alexander Duyck <alexander.h.duyck@linux.intel.com>
---
 hw/virtio/virtio-balloon.c         |   46 ++++++++++++++++++++++++++++++++++--
 include/hw/virtio/virtio-balloon.h |    2 +-
 2 files changed, 45 insertions(+), 3 deletions(-)

```
#### [PATCH 1/3] kcov: remote coverage supportFrom: Andrey Konovalov <andreyknvl@google.com>
##### From: Andrey Konovalov <andreyknvl@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrey Konovalov <andreyknvl@google.com>
X-Patchwork-Id: 11204879
Return-Path: <SRS0=lBCn=YP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EDC4814E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Oct 2019 16:47:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A6754218AE
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Oct 2019 16:47:00 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="Ph51uluY"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389578AbfJVQq7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 22 Oct 2019 12:46:59 -0400
Received: from mail-qk1-f201.google.com ([209.85.222.201]:57002 "EHLO
        mail-qk1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2389456AbfJVQqm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 22 Oct 2019 12:46:42 -0400
Received: by mail-qk1-f201.google.com with SMTP id b29so17163557qka.23
        for <kvm@vger.kernel.org>; Tue, 22 Oct 2019 09:46:41 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=MS7+3RCZOtwmbeNj+jOdYP6GYKkEcz0oEL65PjyrlKc=;
        b=Ph51uluYgh8OJzqGKO4HDiGBbnlA4jyN6fo98qFsZweko4V3OutpH/Yl9J2YUiFNTk
         3wovfpL2GjGwHm+r374oxFaWm7MFPlhB+YZhtXCGyXcl8UsZLThd+t57IsdTpCEKLDz8
         LtI0+RNP/93iAL7a5sOK3Ib1nK0PC4CEYIZhoi98YOzGukqOPr7xYLZRchY6BcY79Zwb
         wZ80gIviRU7/GTYlAR0I2HPcWEXevgdaGlWM676S9Jl/1+xyy9ZwRT3+pwDebjx9Mg1s
         1V/1MAkNDASUVzQ0tN6Aj3rh/p+QdYCHfh5H6Mc5/5GRj7J+q9i0F188QfHLqXz01pPS
         OzfA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=MS7+3RCZOtwmbeNj+jOdYP6GYKkEcz0oEL65PjyrlKc=;
        b=pqSLFTvIwDpCo/RjsGGWoRx8Xz5fCzqNBcL4L5GhdnQzoAPdCZ5L8NFD9i3VV41SMX
         6CDL81W+pwQb8dUPd1+Bd4LnKTrUzKdnYsumkfUEbxsDWS3vyyBWiTkJmUUzW51OR7kT
         vQPoSN8h0swhusFZei096VI/fr4VYl3vPMXxUZ0whu8vqX4OC+knnyH838Ib1N+T067/
         P34zrysLSWsmsccBJB29NHcAsApy0KgwpdY6zx/Jjg65i5AEOxHsfBw1lwk+nACzyb5i
         r3rFQPhJ8XgT/Q0VBIRaasz2cyv3qNA/xw20Tnh78YPM2aYF3ulUQ02fOXYppvRz875g
         9n2w==
X-Gm-Message-State: APjAAAVkOP0HW98ldhJCU5pqBfIDXXXDxSBYtwerhPrNr1f8or+tr7UY
        P7ddrlOW/1Zm+gbJEJBBbf/R/7qtqCiwbRli
X-Google-Smtp-Source: 
 APXvYqwxV1d2DnI/Tyn7PkUtfTlnPcaYAyVWEAF7zEHgwQjP5oQypo4Czgg9zYAiT4quXV2sxsGsCUuhZj382+oX
X-Received: by 2002:a37:a2d1:: with SMTP id
 l200mr3861814qke.158.1571762800725;
 Tue, 22 Oct 2019 09:46:40 -0700 (PDT)
Date: Tue, 22 Oct 2019 18:46:31 +0200
In-Reply-To: <cover.1571762488.git.andreyknvl@google.com>
Message-Id: 
 <df26802a60c09d155291c2abbcb51e4530eb19d7.1571762488.git.andreyknvl@google.com>
Mime-Version: 1.0
References: <cover.1571762488.git.andreyknvl@google.com>
X-Mailer: git-send-email 2.23.0.866.gb869b98d4c-goog
Subject: [PATCH 1/3] kcov: remote coverage support
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
threads: the global ones, that are spawned during kernel boot and are
always running (e.g. USB hub_event()); and the local ones, that are
spawned when a user interacts with some kernel interface (e.g. vhost
workers).

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
the lower 4 bytes are used to denote a handle id within that subsystem.
A reserved value 0 is used as a subsystem id for common handles as they
don't belong to a particular subsystem. The bytes 4-7 are currently
reserved and must be zero. In the future the number of bytes used for the
subsystem or handle ids might be increased.

When a particular userspace proccess collects coverage by via a common
handle, kcov will collect coverage for each code section that is annotated
to use the common handle obtained as kcov_handle from the current
task_struct. However non common handles allow to collect coverage
selectively from different subsystems.

Signed-off-by: Andrey Konovalov <andreyknvl@google.com>
---
 Documentation/dev-tools/kcov.rst | 120 ++++++++
 include/linux/kcov.h             |   6 +
 include/linux/sched.h            |   6 +
 include/uapi/linux/kcov.h        |  20 ++
 kernel/kcov.c                    | 464 ++++++++++++++++++++++++++++---
 5 files changed, 581 insertions(+), 35 deletions(-)

```
#### [PATCH] kvm: cpuid: Expose leaves 0x80000005 and 0x80000006 to the guest
##### From: Jim Mattson <jmattson@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jim Mattson <jmattson@google.com>
X-Patchwork-Id: 11205383
Return-Path: <SRS0=lBCn=YP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 551D313BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Oct 2019 21:34:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 32C72206C2
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Oct 2019 21:34:00 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="oyIA2iT4"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1733123AbfJVVd7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 22 Oct 2019 17:33:59 -0400
Received: from mail-pf1-f202.google.com ([209.85.210.202]:33905 "EHLO
        mail-pf1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1731588AbfJVVd6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 22 Oct 2019 17:33:58 -0400
Received: by mail-pf1-f202.google.com with SMTP id a1so14392480pfn.1
        for <kvm@vger.kernel.org>; Tue, 22 Oct 2019 14:33:58 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=maN1OI3C8rGLXYdMk46F5meV/56/Uajs3NmMIo+9ziM=;
        b=oyIA2iT4jfp/E8ooWHHMvhhM6WbvbYalsKEiLc0XOXOoDEd+zOX7I+H0K2MEqy+YEx
         X4lJemc+Ng0cG5WVp9oFRweqD3HLX3vLAPu/1jtZ/OS+o5L1qkz5yyomvwi4HNBl7/Od
         XjGAb6c2B7eu0q1xLgY95xb0XpiG0+IkaLMxvziLyxByvjEfbah28+hUlru933B2G/oe
         m0nOCvqrkx1pIY+cl6UAyh5mqlAMcI+YEyEJj8klk2t+GqJSGobZ+1CMnU0+Nme0+v5U
         LWv7qygmH59Bfbu4I9/8m/Znlh4nY82S1wG1dhH2NP2jzCyyPIw7+sqKypcniETYzfLg
         OsHA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=maN1OI3C8rGLXYdMk46F5meV/56/Uajs3NmMIo+9ziM=;
        b=FibtRO8DTRDTPMoB3TGgqf3NaT+ARlc6n5bB8lmGnxgAA8NrX74u7ytgWEAt5to8Hq
         OjllCUh/9X6UEGPBx05xDcs41zqV5AKFtc/AFSVEvUvW7vbIxc2imb9CYqaGm2/b3qtc
         mxrRX0Qe4+2S5qMq/TEmKGQt+NoANetOOZ6kGAJ2GfpFKOR7RSrWY5CHXZLmQJonamWn
         u7nA07wySbBxKp4Pi8K6MzQGrvU2doa/WmLFE0NGFAZnK2iozTDHhbwOZozQjHcuGwB1
         azR53yIFFkSU2CkA0tvfZhMJeuOtakcqDUEoB9taMNnSUGtmd/N2RUqemEfpHoyQWyAI
         ROHg==
X-Gm-Message-State: APjAAAVFUW3AhPfGHxNckFS51Mczfmn/sxnGK3jBoqI/+Ub0GIL+2Ixz
        xEovko3HIn5eR+LG8g6sUffZmSmotZgIFLKhJLCMqzUeEKiNNpsCtMOH8C4uw7VINfFW87/8l4A
        q8bQDecEcAqjNVchf5Kf0leKYqRuthIqVIEsrQlQ2c8p/pNRsplVSAuBhX97Hyqo=
X-Google-Smtp-Source: 
 APXvYqwpjchncx6hw+AHJpzPqGA9YF6OKMed2JbxzqV1MY//zXCXLpayE53iKxm98PU2+i8Y+R/+qCF1RTALjA==
X-Received: by 2002:a63:ae02:: with SMTP id q2mr6196324pgf.210.1571780037817;
 Tue, 22 Oct 2019 14:33:57 -0700 (PDT)
Date: Tue, 22 Oct 2019 14:33:49 -0700
Message-Id: <20191022213349.54734-1-jmattson@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.23.0.866.gb869b98d4c-goog
Subject: [PATCH] kvm: cpuid: Expose leaves 0x80000005 and 0x80000006 to the
 guest
From: Jim Mattson <jmattson@google.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Jim Mattson <jmattson@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Leaf 0x80000005 is "L1 Cache and TLB Information." Leaf 0x80000006 is
"L2 Cache and TLB and L3 Cache Information." Include these leaves in
the array returned by KVM_GET_SUPPORTED_CPUID.

Signed-off-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/cpuid.c | 3 +++
 1 file changed, 3 insertions(+)

```
#### [PATCH v2 01/15] KVM: Reinstall old memslots if arch preparation fails
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11203301
Return-Path: <SRS0=lBCn=YP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1023D112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Oct 2019 00:36:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id EDB6821929
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Oct 2019 00:36:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730611AbfJVAfl (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 21 Oct 2019 20:35:41 -0400
Received: from mga07.intel.com ([134.134.136.100]:35282 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730510AbfJVAfl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 21 Oct 2019 20:35:41 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by orsmga105.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 21 Oct 2019 17:35:39 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.67,325,1566889200";
   d="scan'208";a="348897198"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.41])
  by orsmga004.jf.intel.com with ESMTP; 21 Oct 2019 17:35:38 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: James Hogan <jhogan@kernel.org>, Paul Mackerras <paulus@ozlabs.org>,
 Christian Borntraeger <borntraeger@de.ibm.com>,
 Janosch Frank <frankja@linux.ibm.com>, Paolo Bonzini <pbonzini@redhat.com>,
	=?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Marc Zyngier <maz@kernel.org>
Cc: David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        linux-mips@vger.kernel.org, kvm-ppc@vger.kernel.org,
        kvm@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, linux-kernel@vger.kernel.org
Subject: [PATCH v2 01/15] KVM: Reinstall old memslots if arch preparation
 fails
Date: Mon, 21 Oct 2019 17:35:23 -0700
Message-Id: <20191022003537.13013-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.22.0
In-Reply-To: <20191022003537.13013-1-sean.j.christopherson@intel.com>
References: <20191022003537.13013-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Reinstall the old memslots if preparing the new memory region fails
after invalidating a to-be-{re}moved memslot.

Remove the superfluous 'old_memslots' variable so that it's somewhat
clear that the error handling path needs to free the unused memslots,
not simply the 'old' memslots.

Fixes: bc6678a33d9b9 ("KVM: introduce kvm->srcu and convert kvm_set_memory_region to SRCU update")
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 virt/kvm/kvm_main.c | 23 ++++++++++++-----------
 1 file changed, 12 insertions(+), 11 deletions(-)

```
#### [PATCH 01/45] KVM: PPC: Book3S HV: Uninit vCPU if vcore creation fails
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11203579
Return-Path: <SRS0=lBCn=YP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 62D47139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Oct 2019 02:03:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4BB9221929
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Oct 2019 02:03:54 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730768AbfJVB7d (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 21 Oct 2019 21:59:33 -0400
Received: from mga14.intel.com ([192.55.52.115]:61583 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730724AbfJVB7d (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 21 Oct 2019 21:59:33 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by fmsmga103.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 21 Oct 2019 18:59:32 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.67,325,1566889200";
   d="scan'208";a="196293743"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.41])
  by fmsmga008.fm.intel.com with ESMTP; 21 Oct 2019 18:59:31 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Marc Zyngier <maz@kernel.org>, James Hogan <jhogan@kernel.org>,
 Paul Mackerras <paulus@ozlabs.org>,
 Christian Borntraeger <borntraeger@de.ibm.com>,
 Janosch Frank <frankja@linux.ibm.com>, Paolo Bonzini <pbonzini@redhat.com>,
	=?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        linux-mips@vger.kernel.org, kvm-ppc@vger.kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH 01/45] KVM: PPC: Book3S HV: Uninit vCPU if vcore creation
 fails
Date: Mon, 21 Oct 2019 18:58:41 -0700
Message-Id: <20191022015925.31916-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.22.0
In-Reply-To: <20191022015925.31916-1-sean.j.christopherson@intel.com>
References: <20191022015925.31916-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Call kvm_vcpu_uninit() if vcore creation fails to avoid leaking any
resources allocated by kvm_vcpu_init(), i.e. the vcpu->run page.

Fixes: 371fefd6f2dc4 ("KVM: PPC: Allow book3s_hv guests to use SMT processor modes")
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/powerpc/kvm/book3s_hv.c | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
#### [PATCH v12 1/6] mm: Adjust shuffle code to allow for future coalescing
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11205407
Return-Path: <SRS0=lBCn=YP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D443C13BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Oct 2019 22:28:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A8F6D207FC
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Oct 2019 22:28:06 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="OpRegx8/"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388539AbfJVW2C (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 22 Oct 2019 18:28:02 -0400
Received: from mail-pf1-f194.google.com ([209.85.210.194]:37531 "EHLO
        mail-pf1-f194.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1731754AbfJVW2C (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 22 Oct 2019 18:28:02 -0400
Received: by mail-pf1-f194.google.com with SMTP id y5so11532606pfo.4;
        Tue, 22 Oct 2019 15:28:01 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:in-reply-to:references
         :user-agent:mime-version:content-transfer-encoding;
        bh=EpjMfNVSVsAC+zZgTxazNcdbmAOhguRbD3KBWA9AopA=;
        b=OpRegx8/yA7uDdzCE63jc4NvmKoyTk8ZVrcfKLv5SQMX0ImZzoxw9qPH3LNvSrI1Nz
         XWvVc8pZ3v0wdWlObgYoUlRaLHIxxpAuaOYhPC7LQg4PUgZ69B1IbRthaPO1Se37Dc60
         HxlnwMTYlox5JOFsvs3D8dOnbiKXsu52ncGtanxEFsBqIBdWYaLfeiy/hCkqSc3TgHrz
         sLLFKhyLj3+sfcynfbPbqiA8ax4SFEYNuFjLhocXE5tAmnK1XiHFkFB0AG+xx2a3R8kl
         zkorHxFffDrb/l2gX2SIH1Tr0EkHdhwtMt80HpQ8BKCVaYryAzCiacXRxAIizkadGK78
         XWhg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:in-reply-to
         :references:user-agent:mime-version:content-transfer-encoding;
        bh=EpjMfNVSVsAC+zZgTxazNcdbmAOhguRbD3KBWA9AopA=;
        b=Bwl025uJk7fuvhpit/Pxc213VTjFlDoR+vmHH/n5FtnbLT1BMmNOO8a/82UCheiIK2
         r4VbabpzI6MFxE7mWPexy+0EDp0E6k7iTVhPaaKjHZ5HecWujHiz/YjMhiEy3l3AbQRb
         iwGdMxbQyHLnTMcBhyoNb3Vxxq3hL21FZc0YbRxwSA+7e4Fq9ZxjrDmTbbTMRYFFG0/2
         vNt9DD7igAcLtX6SDoOkHYWKACoaSE5U9KLoZgCY79mTjmvgUiF1yl2UjjHNu4a8VeUa
         WHQTZO6gGi4czzkXIWgr/acKvBmad+4jAyoswoNyqTBDPnyIEOgiMwW3VBVvmN3mv5a4
         WQtA==
X-Gm-Message-State: APjAAAVMzlMS5HauUNa122VwfJAMEVnQovpbW+srIPzmRxI3BJ0d0C07
        Y1WMgPE8M1Yhwq/eo/vsexs=
X-Google-Smtp-Source: 
 APXvYqxWCnQaHaoeJNF2ibhbaqRhfocMXlvvK8PUJB9BSUALT2bMDQooty3xH7SndtMI5LNegn1oQQ==
X-Received: by 2002:a63:1b59:: with SMTP id b25mr6351233pgm.267.1571783280678;
        Tue, 22 Oct 2019 15:28:00 -0700 (PDT)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 k123sm12623745pgk.13.2019.10.22.15.27.59
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 22 Oct 2019 15:28:00 -0700 (PDT)
Subject: [PATCH v12 1/6] mm: Adjust shuffle code to allow for future
 coalescing
From: Alexander Duyck <alexander.duyck@gmail.com>
To: kvm@vger.kernel.org, mst@redhat.com, linux-kernel@vger.kernel.org,
        willy@infradead.org, mhocko@kernel.org, linux-mm@kvack.org,
        akpm@linux-foundation.org, mgorman@techsingularity.net,
        vbabka@suse.cz
Cc: yang.zhang.wz@gmail.com, nitesh@redhat.com, konrad.wilk@oracle.com,
        david@redhat.com, pagupta@redhat.com, riel@surriel.com,
        lcapitulino@redhat.com, dave.hansen@intel.com,
        wei.w.wang@intel.com, aarcange@redhat.com, pbonzini@redhat.com,
        dan.j.williams@intel.com, alexander.h.duyck@linux.intel.com,
        osalvador@suse.de
Date: Tue, 22 Oct 2019 15:27:59 -0700
Message-ID: <20191022222759.17338.47308.stgit@localhost.localdomain>
In-Reply-To: <20191022221223.17338.5860.stgit@localhost.localdomain>
References: <20191022221223.17338.5860.stgit@localhost.localdomain>
User-Agent: StGit/0.17.1-dirty
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Alexander Duyck <alexander.h.duyck@linux.intel.com>

Move the head/tail adding logic out of the shuffle code and into the
__free_one_page function since ultimately that is where it is really
needed anyway. By doing this we should be able to reduce the overhead
and can consolidate all of the list addition bits in one spot.

Acked-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Dan Williams <dan.j.williams@intel.com>
Signed-off-by: Alexander Duyck <alexander.h.duyck@linux.intel.com>
---
 include/linux/mmzone.h |   12 --------
 mm/page_alloc.c        |   71 ++++++++++++++++++++++++++++--------------------
 mm/shuffle.c           |   12 ++++----
 mm/shuffle.h           |    6 ++++
 4 files changed, 54 insertions(+), 47 deletions(-)

```
#### [PATCH tip/core/rcu 02/10] x86/kvm/pmu: Replace rcu_swap_protected() with rcu_replace()
##### From: paulmck@kernel.org

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: "Paul E. McKenney" <paulmck@kernel.org>
X-Patchwork-Id: 11205223
Return-Path: <SRS0=lBCn=YP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4AC9D139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Oct 2019 19:13:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 29AC921906
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Oct 2019 19:13:04 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1571771584;
	bh=R3tHkDCH+7tkl14+AOFmzJTymspPmc+OGB4U1M8uKt8=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=UTbLTHFQgF6tubiOjQMXM4VHrwYj07c7ZMh3XqnNsgm7vNy4YBAYH+Y/fUWJ609Jp
	 NqyQkiXjcy9tDWFMeoJFWz+LSyWDeN9uJlXLyGDQ2KrxLOcrfZ/2tl9SfGa00k4caK
	 msKgb9Qhc5j0tBP0uUUjZCejBhTw6YLMKn9eRM/Q=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732930AbfJVTMX (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 22 Oct 2019 15:12:23 -0400
Received: from mail.kernel.org ([198.145.29.99]:43322 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1732903AbfJVTMX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 22 Oct 2019 15:12:23 -0400
Received: from localhost.localdomain (rrcs-50-75-166-42.nys.biz.rr.com
 [50.75.166.42])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id BA37621906;
        Tue, 22 Oct 2019 19:12:20 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1571771542;
        bh=R3tHkDCH+7tkl14+AOFmzJTymspPmc+OGB4U1M8uKt8=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=0OLUuUOtRdP0jRyYAWW6w0ldh8KU81QVmuon8dGG0kMSUUYvmJjbSVfLR89zD3gQE
         5vj7iWGw2mBo28bqITekuThcLemKYXHga/pRsJ76gOazKfJnea/kPy8+rj+QPOFKIV
         xoBV4vf7tOVsT1p7GcTghDLLhiFFlRYNn+ZBsBw4=
From: paulmck@kernel.org
To: rcu@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, mingo@kernel.org, jiangshanlai@gmail.com,
 dipankar@in.ibm.com, akpm@linux-foundation.org,
 mathieu.desnoyers@efficios.com, josh@joshtriplett.org, tglx@linutronix.de,
 peterz@infradead.org, rostedt@goodmis.org, dhowells@redhat.com,
 edumazet@google.com, fweisbec@gmail.com, oleg@redhat.com,
 joel@joelfernandes.org, "Paul E. McKenney" <paulmck@kernel.org>,
	=?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
 "H. Peter Anvin" <hpa@zytor.com>, x86@kernel.org, kvm@vger.kernel.org
Subject: [PATCH tip/core/rcu 02/10] x86/kvm/pmu: Replace rcu_swap_protected()
 with rcu_replace()
Date: Tue, 22 Oct 2019 12:12:07 -0700
Message-Id: <20191022191215.25781-2-paulmck@kernel.org>
X-Mailer: git-send-email 2.9.5
In-Reply-To: <20191022191136.GA25627@paulmck-ThinkPad-P72>
References: <20191022191136.GA25627@paulmck-ThinkPad-P72>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: "Paul E. McKenney" <paulmck@kernel.org>

This commit replaces the use of rcu_swap_protected() with the more
intuitively appealing rcu_replace() as a step towards removing
rcu_swap_protected().

Link: https://lore.kernel.org/lkml/CAHk-=wiAsJLw1egFEE=Z7-GGtM6wcvtyytXZA1+BHqta4gg6Hw@mail.gmail.com/
Reported-by: Linus Torvalds <torvalds@linux-foundation.org>
[ paulmck: From rcu_replace() to rcu_replace_pointer() per Ingo Molnar. ]
Signed-off-by: Paul E. McKenney <paulmck@kernel.org>
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
Cc: "Radim Krčmář" <rkrcmar@redhat.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Borislav Petkov <bp@alien8.de>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: <x86@kernel.org>
Cc: <kvm@vger.kernel.org>
---
 arch/x86/kvm/pmu.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [kvm-unit-tests PATCH v1 1/5] s390x: remove redundant defines
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 11204245
Return-Path: <SRS0=lBCn=YP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7FC1F14ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Oct 2019 10:53:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6871021872
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Oct 2019 10:53:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730684AbfJVKxO (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 22 Oct 2019 06:53:14 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:28164 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1730379AbfJVKxN (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 22 Oct 2019 06:53:13 -0400
Received: from pps.filterd (m0098399.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x9MAmSWY071852
        for <kvm@vger.kernel.org>; Tue, 22 Oct 2019 06:53:12 -0400
Received: from e06smtp03.uk.ibm.com (e06smtp03.uk.ibm.com [195.75.94.99])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2vsweyxp5j-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Tue, 22 Oct 2019 06:53:12 -0400
Received: from localhost
        by e06smtp03.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <imbrenda@linux.ibm.com>;
        Tue, 22 Oct 2019 11:53:10 +0100
Received: from b06cxnps4075.portsmouth.uk.ibm.com (9.149.109.197)
        by e06smtp03.uk.ibm.com (192.168.101.133) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Tue, 22 Oct 2019 11:53:06 +0100
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06cxnps4075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x9MAr5Iu24772646
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 22 Oct 2019 10:53:05 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 521D052050;
        Tue, 22 Oct 2019 10:53:05 +0000 (GMT)
Received: from p-imbrenda.boeblingen.de.ibm.com (unknown [9.152.224.39])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTPS id 0FF575204E;
        Tue, 22 Oct 2019 10:53:05 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, thuth@redhat.com, david@redhat.com,
        borntraeger@de.ibm.com, frankja@linux.ibm.com
Subject: [kvm-unit-tests PATCH v1 1/5] s390x: remove redundant defines
Date: Tue, 22 Oct 2019 12:53:00 +0200
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1571741584-17621-1-git-send-email-imbrenda@linux.ibm.com>
References: <1571741584-17621-1-git-send-email-imbrenda@linux.ibm.com>
X-TM-AS-GCONF: 00
x-cbid: 19102210-0012-0000-0000-0000035B6D1B
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19102210-0013-0000-0000-0000219697A0
Message-Id: <1571741584-17621-2-git-send-email-imbrenda@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-10-22_03:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=915 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1908290000 definitions=main-1910220098
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Reviewed-by: Christian Borntraeger <borntraeger@de.ibm.com>
Reviewed-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
---
 lib/s390x/sclp.h | 2 --
 1 file changed, 2 deletions(-)

```
#### [PATCH v12 QEMU 1/3] virtio-ballon: Implement support for page poison tracking feature
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11205431
Return-Path: <SRS0=lBCn=YP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 076C4913
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Oct 2019 22:29:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CFC5D2086D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Oct 2019 22:29:31 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="QgMli6JN"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387731AbfJVW32 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 22 Oct 2019 18:29:28 -0400
Received: from mail-pl1-f178.google.com ([209.85.214.178]:41648 "EHLO
        mail-pl1-f178.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1731754AbfJVW31 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 22 Oct 2019 18:29:27 -0400
Received: by mail-pl1-f178.google.com with SMTP id t10so9018706plr.8;
        Tue, 22 Oct 2019 15:29:27 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:in-reply-to:references
         :user-agent:mime-version:content-transfer-encoding;
        bh=yOvpSx16yNanZpbvFfAUMxFv0SM7m3MFplEES/wscuI=;
        b=QgMli6JNIa56lL4eAZjs4pfKYgvRfY83C3icZn+eI1FE8sDdU+DB4J4YSwoTKQ6tvW
         jcUMidPNUp9KYSGEB6M2WO0u2ykMi3pKLu9EHekLfQLpsNsPjD+DN5yFVPIQ2Q9f7CMz
         QkBLk27mQya8gYye4RtaXvoX26cFg8GKqwsZrFumhQ1X1QA+YgD5vKfMVydTJEfbRvMi
         8RJgj+mQkJsyWc1AF9mjCBXh1QtHKWd29Sg2cU/A5J+pwD5hJidZKX8F26jQIYlfDPpC
         6cxe+9eFuJRmZAPB8HMUn/9U5REqAdtmG2DwnFAwMBTT8h0IgllYGK5L6mHUuwoJkDvU
         gvKA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:in-reply-to
         :references:user-agent:mime-version:content-transfer-encoding;
        bh=yOvpSx16yNanZpbvFfAUMxFv0SM7m3MFplEES/wscuI=;
        b=stGsWfp9tgIG1+NCeUAXqJ/MN3h3GThID0cAQkO30jD6zGW1qX7BRwBJIGdIjSZoh2
         NKg+ioKbgxFZWLlhOdoOb/0/Yu7sY7REsHDGH0UY9QeC2Drs0ACznCZfVXue00VATIDz
         WBfVN/T/ZNlyXubkwFRHnEorVdJxqAXR6epK9fHWMnIovzTyZdBVTc2EpPD7bidTC4//
         yjG57li9Bvqedhyp7iWtAoJBsrmqo8hkMlhgqfas3p62fuZluMV/GCliT7aXvwAbnLdl
         pyXxEhEezyWNhyN8iuFXwNm0rzmpNrdDtV5kHdFmhuOVOvOuAsWLyD4uveCu2ouTPNwR
         6W9g==
X-Gm-Message-State: APjAAAUAxrDefZ29vdhzoX+FyfezdM03p96GVp7RlkTO2CDYEacLjxth
        sW1susqa/s744OHJ39rEUtY=
X-Google-Smtp-Source: 
 APXvYqwOh3sC8MEliztTGSI17R5c3+FpiIbUmfEJa0adlCVsRf/Z1r9ugObvgB5CZ9HEIz5WhkZy5w==
X-Received: by 2002:a17:902:b489:: with SMTP id
 y9mr6242540plr.9.1571783366380;
        Tue, 22 Oct 2019 15:29:26 -0700 (PDT)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 2sm21453852pfo.91.2019.10.22.15.29.25
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 22 Oct 2019 15:29:25 -0700 (PDT)
Subject: [PATCH v12 QEMU 1/3] virtio-ballon: Implement support for page
 poison tracking feature
From: Alexander Duyck <alexander.duyck@gmail.com>
To: kvm@vger.kernel.org, mst@redhat.com, linux-kernel@vger.kernel.org,
        willy@infradead.org, mhocko@kernel.org, linux-mm@kvack.org,
        akpm@linux-foundation.org, mgorman@techsingularity.net,
        vbabka@suse.cz
Cc: yang.zhang.wz@gmail.com, nitesh@redhat.com, konrad.wilk@oracle.com,
        david@redhat.com, pagupta@redhat.com, riel@surriel.com,
        lcapitulino@redhat.com, dave.hansen@intel.com,
        wei.w.wang@intel.com, aarcange@redhat.com, pbonzini@redhat.com,
        dan.j.williams@intel.com, alexander.h.duyck@linux.intel.com,
        osalvador@suse.de
Date: Tue, 22 Oct 2019 15:29:25 -0700
Message-ID: <20191022222925.17594.38701.stgit@localhost.localdomain>
In-Reply-To: <20191022221223.17338.5860.stgit@localhost.localdomain>
References: <20191022221223.17338.5860.stgit@localhost.localdomain>
User-Agent: StGit/0.17.1-dirty
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Alexander Duyck <alexander.h.duyck@linux.intel.com>

We need to make certain to advertise support for page poison tracking if
we want to actually get data on if the guest will be poisoning pages. So
if free page hinting is active we should add page poisoning support and
let the guest disable it if it isn't using it.

Page poisoning will result in a page being dirtied on free. As such we
cannot really avoid having to copy the page at least one more time since
we will need to write the poison value to the destination. As such we can
just ignore free page hinting if page poisoning is enabled as it will
actually reduce the work we have to do.

Signed-off-by: Alexander Duyck <alexander.h.duyck@linux.intel.com>
---
 hw/virtio/virtio-balloon.c         |   25 +++++++++++++++++++++----
 include/hw/virtio/virtio-balloon.h |    1 +
 2 files changed, 22 insertions(+), 4 deletions(-)

```
#### [PATCH v2] vhost: introduce mdev based hardware backend
##### From: Tiwei Bie <tiwei.bie@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tiwei Bie <tiwei.bie@intel.com>
X-Patchwork-Id: 11204093
Return-Path: <SRS0=lBCn=YP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6B34A1515
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Oct 2019 09:56:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 371DD218AE
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Oct 2019 09:56:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731614AbfJVJ4Y (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 22 Oct 2019 05:56:24 -0400
Received: from mga14.intel.com ([192.55.52.115]:34734 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728182AbfJVJ4Y (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 22 Oct 2019 05:56:24 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga006.fm.intel.com ([10.253.24.20])
  by fmsmga103.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 22 Oct 2019 02:56:23 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.67,326,1566889200";
   d="scan'208";a="398965385"
Received: from dpdk-virtio-tbie-2.sh.intel.com ([10.67.104.74])
  by fmsmga006.fm.intel.com with ESMTP; 22 Oct 2019 02:56:21 -0700
From: Tiwei Bie <tiwei.bie@intel.com>
To: mst@redhat.com, jasowang@redhat.com, alex.williamson@redhat.com,
        maxime.coquelin@redhat.com
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        dan.daly@intel.com, cunming.liang@intel.com,
        zhihong.wang@intel.com, lingshan.zhu@intel.com, tiwei.bie@intel.com
Subject: [PATCH v2] vhost: introduce mdev based hardware backend
Date: Tue, 22 Oct 2019 17:52:29 +0800
Message-Id: <20191022095230.2514-1-tiwei.bie@intel.com>
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
https://lkml.org/lkml/2019/10/17/286

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

 drivers/vfio/mdev/mdev_core.c |  12 +
 drivers/vhost/Kconfig         |   9 +
 drivers/vhost/Makefile        |   3 +
 drivers/vhost/mdev.c          | 415 ++++++++++++++++++++++++++++++++++
 include/linux/mdev.h          |   3 +
 include/uapi/linux/vhost.h    |  13 ++
 6 files changed, 455 insertions(+)
 create mode 100644 drivers/vhost/mdev.c

```
#### [PATCH kvm-unit-tests 1/4] x86: hyperv_stimer: keep SINT number parameter in 'struct stimer'
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11204745
Return-Path: <SRS0=lBCn=YP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0E4361515
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Oct 2019 15:56:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E18972053B
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 22 Oct 2019 15:56:22 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="fEuYkPEy"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732091AbfJVP4W (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 22 Oct 2019 11:56:22 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:43834 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1731793AbfJVP4V (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 22 Oct 2019 11:56:21 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1571759779;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=XxjDNqjz6jOgBTYwePDqWFKfY8jBva/lRjE5JWzfDtc=;
        b=fEuYkPEy1w89k/6riNdh9t/R2SPvdU9utBShXUIVRfmxgeQhO32BlwdAXu+mZYAS44O/B0
        xR819bWO6PTDzTNxbGoDMjJ3BVILRlgM+9+2WFEoT3Nxfi7yxqSLydATMCrdj+iP2sApBU
        r8TnrDHYUZe3kZfyu7sF7amIbF3JS1Q=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-4-jgCgPTQgNzy1hyZntvDYVA-1; Tue, 22 Oct 2019 11:56:16 -0400
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 89ACC800D49;
        Tue, 22 Oct 2019 15:56:15 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.43.2.155])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 70B1A5D6A9;
        Tue, 22 Oct 2019 15:56:12 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Roman Kagan <rkagan@virtuozzo.com>
Subject: [PATCH kvm-unit-tests 1/4] x86: hyperv_stimer: keep SINT number
 parameter in 'struct stimer'
Date: Tue, 22 Oct 2019 17:56:05 +0200
Message-Id: <20191022155608.8001-2-vkuznets@redhat.com>
In-Reply-To: <20191022155608.8001-1-vkuznets@redhat.com>
References: <20191022155608.8001-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
X-MC-Unique: jgCgPTQgNzy1hyZntvDYVA-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

As a preparation to enabling direct synthetic timers support stop
passing SINT number to stimer_start.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 x86/hyperv_stimer.c | 28 +++++++++++++++++++---------
 1 file changed, 19 insertions(+), 9 deletions(-)

```
