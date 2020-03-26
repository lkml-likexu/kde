#### [PATCH v2 2/3] Teach SELinux about anonymous inodesFrom: Daniel Colascione <dancol@google.com>
##### From: Daniel Colascione <dancol@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Daniel Colascione <dancol@google.com>
X-Patchwork-Id: 11458879
Return-Path: <SRS0=cO5m=5K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 22436161F
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Mar 2020 23:03:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 02E6D2073E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Mar 2020 23:03:55 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="t2o7JXy6"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727650AbgCYXDy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 25 Mar 2020 19:03:54 -0400
Received: from mail-pf1-f201.google.com ([209.85.210.201]:45224 "EHLO
        mail-pf1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727501AbgCYXDx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 25 Mar 2020 19:03:53 -0400
Received: by mail-pf1-f201.google.com with SMTP id a188so3526640pfa.12
        for <kvm@vger.kernel.org>; Wed, 25 Mar 2020 16:03:51 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=NvPoNDqt/FtxcJkV8j34y/lYvSuomfgx7WmZT8gVSSI=;
        b=t2o7JXy6smRSIz1Gof8XTM1mwfU4ibv7GB/FwKt0T9Ic9FsXuqErsqSRXcgIYxhCtw
         qV59nSIKz7sbvDk6aFEi5WuCNKeiKiBl7L6ezlLl4NdtcYN3LBtOtAzkKX+UMfn5CJ/a
         3tO9v4eBXJnHXx6acNqbCEj3JE0Iprd4DulA5Pmc3YygJ6jh3QdOG19BgyGY2mvNM75r
         oqRKCbFGw1fN/lSF34NwbDA3gDZK07IoyTRMsl/8RRQwSBdTupYcdNMMPCLgSQ5gf8MX
         I3zW20Tk6Y78ZynrY2eLb4g6a4mC7ddBMlA8jur2LvN325K6PqhQghfwQfZmF63bETjs
         VbRw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=NvPoNDqt/FtxcJkV8j34y/lYvSuomfgx7WmZT8gVSSI=;
        b=RbvLxV6W2FhMSswE1fIdE6jAjXLvL5dFuJFU532CZiXhqYn9/qC6ObGX5H7S2VJkXI
         GKEeuMd8dViUKecnkQjmm9jPCTzORXLzu8rkpVQMM7kity/H7+cABLqh/6Pa7x5qJ+pQ
         RnXfkaFD8zJTXhq6EcNF71BC1+bHUHwif0/cvBvTlZx3l1LP/2gSIeTbiiziZPlvTsR0
         ZN5fPGkYIGmsbBEc/wo3z/7tZki+nJb7f/RYsGLqWqJSZHPg/WkR9+XQZci/jxIu252U
         ykgWBmoJMcrS447kCzWg/D/9VIc7WilOWfbWgUKB6OU7eLO5low5w+7rPJuZxY2/5SMe
         7gFQ==
X-Gm-Message-State: ANhLgQ04zcua1VgF51ao2bDvfSVCtK95+NI7bz/T256B9rzUGOZ9ie9I
        BsPQn5QfmDo/MS/aLdAqeliqnvtnss0=
X-Google-Smtp-Source: 
 ADFU+vucmD0Yz2UW/2xYbr0QyEKdkrlHqcCxt3u/qpa+E0wkrqbKGWIfaK2NSVY0SRYNCtko5UlfpW5yfws=
X-Received: by 2002:a63:28c:: with SMTP id 134mr5251204pgc.165.1585177430117;
 Wed, 25 Mar 2020 16:03:50 -0700 (PDT)
Date: Wed, 25 Mar 2020 16:02:47 -0700
In-Reply-To: <20200214032635.75434-1-dancol@google.com>
Message-Id: <20200325230245.184786-3-dancol@google.com>
Mime-Version: 1.0
References: <20200214032635.75434-1-dancol@google.com>
X-Mailer: git-send-email 2.25.1.696.g5e7596f4ac-goog
Subject: [PATCH v2 2/3] Teach SELinux about anonymous inodes
From: Daniel Colascione <dancol@google.com>
To: timmurray@google.com, selinux@vger.kernel.org,
        linux-security-module@vger.kernel.org,
        linux-fsdevel@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, viro@zeniv.linux.org.uk, paul@paul-moore.com,
        nnk@google.com, sds@tycho.nsa.gov, lokeshgidra@google.com
Cc: Daniel Colascione <dancol@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This change uses the anon_inodes and LSM infrastructure introduced in
the previous patch to give SELinux the ability to control
anonymous-inode files that are created using the new _secure()
anon_inodes functions.

A SELinux policy author detects and controls these anonymous inodes by
adding a name-based type_transition rule that assigns a new security
type to anonymous-inode files created in some domain. The name used
for the name-based transition is the name associated with the
anonymous inode for file listings --- e.g., "[userfaultfd]" or
"[perf_event]".

Example:

type uffd_t;
type_transition sysadm_t sysadm_t : file uffd_t "[userfaultfd]";
allow sysadm_t uffd_t:file { create };

(The next patch in this series is necessary for making userfaultfd
support this new interface.  The example above is just
for exposition.)

Signed-off-by: Daniel Colascione <dancol@google.com>
---
 security/selinux/hooks.c            | 54 +++++++++++++++++++++++++++++
 security/selinux/include/classmap.h |  2 ++
 2 files changed, 56 insertions(+)

```
#### [PATCH v2 3/3] Wire UFFD up to SELinuxFrom: Daniel Colascione <dancol@google.com>
##### From: Daniel Colascione <dancol@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Daniel Colascione <dancol@google.com>
X-Patchwork-Id: 11458887
Return-Path: <SRS0=cO5m=5K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BA489161F
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Mar 2020 23:04:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9CB322076A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Mar 2020 23:04:05 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="i7ZOUHjb"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727653AbgCYXEE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 25 Mar 2020 19:04:04 -0400
Received: from mail-ua1-f73.google.com ([209.85.222.73]:33980 "EHLO
        mail-ua1-f73.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727358AbgCYXEE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 25 Mar 2020 19:04:04 -0400
Received: by mail-ua1-f73.google.com with SMTP id 42so1570642uar.1
        for <kvm@vger.kernel.org>; Wed, 25 Mar 2020 16:04:03 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=REBj1fgB1itW3afNpdBeCKHTfmMER4muP4nMI9CXCW4=;
        b=i7ZOUHjbFgVx+s0UVSJIf8vLWEPboaP6kvpQJDJL8TGrAnhcez44af9mv/98ocfWvE
         GYIilsL5kfd5pBocqpSxRvgmC6d4prkhqUf6/hAq0fzS9gyQBoAqZDnaDyj6BDqkos5n
         WMn3smxCXwJBxZUygM0ar+EiLI8WqAA2U3mNbN/HevW0K9j2aMdlG7sgml+Z1FphTgG5
         Q5go7scoS9bb5Ql8ljMb2itbIVAq8j5ALe6yGzKx49cTmyrknkkLRIwiDaCfmn9uk5Ce
         ZepD2ALjcmb8yILx8yJS8mqMhxVHW2hUWj6XhS7YPWe15bEY6nCH1QAZ9aJIdW5/dKDh
         2WUQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=REBj1fgB1itW3afNpdBeCKHTfmMER4muP4nMI9CXCW4=;
        b=kwa/Hq7hK42+qY6fOqPWLhbPkb1HuD7p8hm7vzhXvO3jE+sPC11wJsGBstnwW+BLtZ
         HryX1LPd5H+vkYkvJ4trFhPtxpnuwbYtIi+Gx2fMG/IZgZQv7FBKQN5j/44uZwBcu0OS
         atlVAuawEmarCvkaFAqMsgA4HRD9+fPQ1UmhGvXbrtS4aR96gqyVixN0n1s/VErlz1h3
         P2ahnRoNUNNl6dbC0CA7dvBiJTIBFHbxOItrR8MMUy03t/kRhbW1TQr8h2gyPmw0GwQj
         tuKx2Ivgwy2A76NryY+8AyPz0yuk/NRLmcQjr9TYfnMA9ilezA1HgVOhVMxUiai5jkSO
         AqNg==
X-Gm-Message-State: ANhLgQ1L5dhXlT3wGr9AJv9UeTPEnEHo592ePwC7YH+rsYxRJ2HqEiqC
        N5OsG9JORPiPJ9UL70us9bGELutONWk=
X-Google-Smtp-Source: 
 ADFU+vs7IQhEMaKxtqnr+moo0vZvstvYbRtR5UCcCU4RfI+0ZcWfHjbWDnDHCtb/iWz2nYKBCZvXwQ28Ff8=
X-Received: by 2002:a1f:f884:: with SMTP id w126mr4386443vkh.41.1585177443359;
 Wed, 25 Mar 2020 16:04:03 -0700 (PDT)
Date: Wed, 25 Mar 2020 16:02:49 -0700
In-Reply-To: <20200214032635.75434-1-dancol@google.com>
Message-Id: <20200325230245.184786-4-dancol@google.com>
Mime-Version: 1.0
References: <20200214032635.75434-1-dancol@google.com>
X-Mailer: git-send-email 2.25.1.696.g5e7596f4ac-goog
Subject: [PATCH v2 3/3] Wire UFFD up to SELinux
From: Daniel Colascione <dancol@google.com>
To: timmurray@google.com, selinux@vger.kernel.org,
        linux-security-module@vger.kernel.org,
        linux-fsdevel@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, viro@zeniv.linux.org.uk, paul@paul-moore.com,
        nnk@google.com, sds@tycho.nsa.gov, lokeshgidra@google.com
Cc: Daniel Colascione <dancol@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This change gives userfaultfd file descriptors a real security
context, allowing policy to act on them.

Signed-off-by: Daniel Colascione <dancol@google.com>
---
 fs/userfaultfd.c | 34 +++++++++++++++++++++++++++++-----
 1 file changed, 29 insertions(+), 5 deletions(-)

```
#### [PATCH v2 1/6] selftests: Create directory when OUTPUT specified
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11457967
Return-Path: <SRS0=cO5m=5K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3EDFD1731
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Mar 2020 14:19:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1F36D20CC7
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Mar 2020 14:19:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727707AbgCYOTM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 25 Mar 2020 10:19:12 -0400
Received: from mga04.intel.com ([192.55.52.120]:42324 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727505AbgCYOTL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 25 Mar 2020 10:19:11 -0400
IronPort-SDR: 
 gXYpgOiS8QxktuKIAtLDG3QsmRtve/otHRnsBw45b99XqkJFW9q33QdVhTiX+I1kcLoSWc21E0
 NJfWVzeB4kmA==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 25 Mar 2020 07:19:11 -0700
IronPort-SDR: 
 AbZJ1HHcIw0fp+5/Lfc/do6mA+kSLGmHIYjxgBaP2nI33NpXdYsbbyawUwK1AD3HfREyBq2Hnx
 tUg5Eavt/Scw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,304,1580803200";
   d="scan'208";a="270811075"
Received: from lxy-clx-4s.sh.intel.com ([10.239.43.39])
  by fmsmga004.fm.intel.com with ESMTP; 25 Mar 2020 07:19:10 -0700
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Shuah Khan <shuah@kernel.org>, Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org, linux-kselftest@vger.kernel.org,
        linux-kernel@vger.kernel.org, Xiaoyao Li <xiaoyao.li@intel.com>
Subject: [PATCH v2 1/6] selftests: Create directory when OUTPUT specified
Date: Wed, 25 Mar 2020 22:01:28 +0800
Message-Id: <20200325140133.103236-2-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20200325140133.103236-1-xiaoyao.li@intel.com>
References: <20200325140133.103236-1-xiaoyao.li@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When OUTPUT specified, it may encounter no directory error if there is
subdir in $TARGET for any of TEST_GEN_PROGS, TEST_GEN_PROGS_EXTENDED, or
TEST_GEN_FILES.

This issue is found by running

	make OUTPUT=/path/to/output

in tools/testing/selftests/kvm

Signed-off-by: Xiaoyao Li <xiaoyao.li@intel.com>
---
 tools/testing/selftests/lib.mk | 10 ++++++++++
 1 file changed, 10 insertions(+)

```
#### [PATCH 1/3] KVM/memslot: Move the initial set of dirty bitmap to arch
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 11456929
Return-Path: <SRS0=cO5m=5K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EA83A1667
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Mar 2020 04:27:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CA81E20774
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Mar 2020 04:27:02 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726313AbgCYE0t (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 25 Mar 2020 00:26:49 -0400
Received: from szxga06-in.huawei.com ([45.249.212.32]:39234 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726206AbgCYE0t (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 25 Mar 2020 00:26:49 -0400
Received: from DGGEMS408-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id 15AD56D2D2F65F81D46A;
        Wed, 25 Mar 2020 12:26:44 +0800 (CST)
Received: from linux-kDCJWP.huawei.com (10.175.104.212) by
 DGGEMS408-HUB.china.huawei.com (10.3.19.208) with Microsoft SMTP Server id
 14.3.487.0; Wed, 25 Mar 2020 12:26:33 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <kvm@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>,
        <kvmarm@lists.cs.columbia.edu>
CC: Marc Zyngier <maz@kernel.org>, Paolo Bonzini <pbonzini@redhat.com>,
        "James Morse" <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Will Deacon <will@kernel.org>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Jay Zhou <jianjay.zhou@huawei.com>,
        <wanghaibin.wang@huawei.com>, Keqian Zhu <zhukeqian1@huawei.com>
Subject: [PATCH 1/3] KVM/memslot: Move the initial set of dirty bitmap to arch
Date: Wed, 25 Mar 2020 12:24:21 +0800
Message-ID: <20200325042423.12181-2-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.19.1
In-Reply-To: <20200325042423.12181-1-zhukeqian1@huawei.com>
References: <20200325042423.12181-1-zhukeqian1@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.175.104.212]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Currently, when KVM_DIRTY_LOG_INITIALLY_SET is enabled, the initial set
of memslot dirty bitmap is located at arch shared path. By making this
implementation be architecture depended, we can realize some architecture
depended optimizations (e.g. Only mark dirty for these pages with valid
translation entries, then userspace can use this information to only send
these pages during migration).

Signed-off-by: Keqian Zhu <zhukeqian1@huawei.com>
---
 arch/x86/kvm/x86.c  | 3 +++
 virt/kvm/kvm_main.c | 3 ---
 2 files changed, 3 insertions(+), 3 deletions(-)

```
#### [PATCH] KVM: x86: Fix BUILD_BUG() in __cpuid_entry_get_reg() w/ CONFIG_UBSAN=y
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11458489
Return-Path: <SRS0=cO5m=5K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AA29D92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Mar 2020 19:13:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9363820658
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Mar 2020 19:13:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727444AbgCYTNB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 25 Mar 2020 15:13:01 -0400
Received: from mga17.intel.com ([192.55.52.151]:19925 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727279AbgCYTNA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 25 Mar 2020 15:13:00 -0400
IronPort-SDR: 
 8UlUOX3Q1KxquXMkk7WywKVPP2/PAa0BMP7JaVNFaubPQwGnTyucWhxe2HyisQiSCQFGDOfC3Q
 8Mqc0KIuq/Gw==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by fmsmga107.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 25 Mar 2020 12:13:00 -0700
IronPort-SDR: 
 bQeRBDjYsYwoIzI4XP0Iyc8k6ExUzw5Fb7NEfqduEHTmrXqzi1+unrBqE9U+ap/POV/I74TBMc
 zeoLXjwt43Rw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,305,1580803200";
   d="scan'208";a="357902461"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga001.fm.intel.com with ESMTP; 25 Mar 2020 12:13:00 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Randy Dunlap <rdunlap@infradead.org>
Subject: [PATCH] KVM: x86: Fix BUILD_BUG() in __cpuid_entry_get_reg() w/
 CONFIG_UBSAN=y
Date: Wed, 25 Mar 2020 12:12:59 -0700
Message-Id: <20200325191259.23559-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Take the target reg in __cpuid_entry_get_reg() instead of a pointer to a
struct cpuid_reg.  When building with -fsanitize=alignment (enabled by
CONFIG_UBSAN=y), some versions of gcc get tripped up on the pointer and
trigger the BUILD_BUG().

Reported-by: Randy Dunlap <rdunlap@infradead.org>
Fixes: d8577a4c238f8 ("KVM: x86: Do host CPUID at load time to mask KVM cpu caps")
Fixes: 4c61534aaae2a ("KVM: x86: Introduce cpuid_entry_{get,has}() accessors")
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Acked-by: Randy Dunlap <rdunlap@infradead.org> # build-tested
---
 arch/x86/kvm/cpuid.c | 2 +-
 arch/x86/kvm/cpuid.h | 8 ++++----
 2 files changed, 5 insertions(+), 5 deletions(-)

```
#### 
##### 

```c
```
#### [PATCH v2 1/3] Add a new LSM-supporting anonymous inode interfaceFrom: Daniel Colascione <dancol@google.com>
##### From: Daniel Colascione <dancol@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Daniel Colascione <dancol@google.com>
X-Patchwork-Id: 11458873
Return-Path: <SRS0=cO5m=5K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E8A65161F
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Mar 2020 23:03:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id AB2D820737
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Mar 2020 23:03:35 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="QfRqIWQx"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727505AbgCYXDe (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 25 Mar 2020 19:03:34 -0400
Received: from mail-pl1-f201.google.com ([209.85.214.201]:33930 "EHLO
        mail-pl1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727399AbgCYXDe (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 25 Mar 2020 19:03:34 -0400
Received: by mail-pl1-f201.google.com with SMTP id j8so2877363plk.1
        for <kvm@vger.kernel.org>; Wed, 25 Mar 2020 16:03:32 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=zFlM70MP3VetVuidGZ5oQERxbIVr8cobPoAE2yMCfNg=;
        b=QfRqIWQxIxnf9OwiR3qwuo5ZC3XNS64e2/LIx4O/LpNntFvwQNJ9Anko32bz5vYgYI
         pWVGpn7zrfIopsO9TuykQlOXDYNpQS2JfI59xzQPtRsKQHjYlGDeROLwLP1CIAqxYMvz
         Ug5MEzqDqffwgFOSPRRA+lKUS16egvFnYV3k7aV7V9RBv732wIpCqLw4Hhhtn91Kv9YX
         fGl8PwY2T8ySh5lM9Q+wo6LfZFgeECjJMVaqaD8k+AMkHHq8JCU2XaWtSlLqOMA0041u
         1iH1BaCtdw3MBwi2H/4nLZf8F8sKpyGJ/29AOJ0yWMlCrSt5AA+iXwb4cPLeWWevGg/q
         MOrA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=zFlM70MP3VetVuidGZ5oQERxbIVr8cobPoAE2yMCfNg=;
        b=BopEYF1Q0IJEjnsfWFNsV/DJnN3tgJgGr8KLTP0v1MXPVATVD8CtK1bH4Hv7ukcCvZ
         47mRyt7T6jNuE/Ik0axa2ZNvL5mi+5DoHd9wfDwkDxtgN5DhPg4bWB6GZ40yzhyZxckb
         HLJbp4fS7XggO7a0De6Vo4olWzdbmGlDTQARklVDkoQngduKF6v3AlQb9i7rFM3wGbd+
         MFUfb187j1ABhEHthG6mTT9J9i6xYoY3sNKkDjdyDUCys4wJg2wjxkYKsCnd8drTOeD+
         gyluoEm/RDT3sUrCJwIJA3J1BSgXfsOpBGblpQoKGyV9mf8t/tUTdDSgEU+txv4s6wJq
         /iFw==
X-Gm-Message-State: ANhLgQ01Nuu5dMhzBHuwx/7nGCR2z5lR8+AzKhFS54AHymRRRycx8RyK
        ms/kUfeN4D5s48o3ELRwCFt5v78/y1M=
X-Google-Smtp-Source: 
 ADFU+vtU9lb3yIGxPT2ov7+t+v8Awako5KFnSxIy/i+ruF06YaytkVMQbG3xlST/+cyHkk6zWwPLi/afuNo=
X-Received: by 2002:a17:90a:fa08:: with SMTP id
 cm8mr6194695pjb.144.1585177412202;
 Wed, 25 Mar 2020 16:03:32 -0700 (PDT)
Date: Wed, 25 Mar 2020 16:02:45 -0700
In-Reply-To: <20200214032635.75434-1-dancol@google.com>
Message-Id: <20200325230245.184786-2-dancol@google.com>
Mime-Version: 1.0
References: <20200214032635.75434-1-dancol@google.com>
X-Mailer: git-send-email 2.25.1.696.g5e7596f4ac-goog
Subject: [PATCH v2 1/3] Add a new LSM-supporting anonymous inode interface
From: Daniel Colascione <dancol@google.com>
To: timmurray@google.com, selinux@vger.kernel.org,
        linux-security-module@vger.kernel.org,
        linux-fsdevel@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, viro@zeniv.linux.org.uk, paul@paul-moore.com,
        nnk@google.com, sds@tycho.nsa.gov, lokeshgidra@google.com
Cc: Daniel Colascione <dancol@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This change adds two new functions, anon_inode_getfile_secure and
anon_inode_getfd_secure, that create anonymous-node files with
individual non-S_PRIVATE inodes to which security modules can apply
policy. Existing callers continue using the original singleton-inode
kind of anonymous-inode file. We can transition anonymous inode users
to the new kind of anonymous inode in individual patches for the sake
of bisection and review.

The new functions accept an optional context_inode parameter that
callers can use to provide additional contextual information to
security modules, e.g., indicating that one anonymous struct file is a
logical child of another, allowing a security model to propagate
security information from one to the other.

Signed-off-by: Daniel Colascione <dancol@google.com>
---
 fs/anon_inodes.c            | 196 ++++++++++++++++++++++++++++--------
 fs/userfaultfd.c            |   4 +-
 include/linux/anon_inodes.h |  13 +++
 include/linux/lsm_hooks.h   |   9 ++
 include/linux/security.h    |   4 +
 security/security.c         |  10 ++
 6 files changed, 191 insertions(+), 45 deletions(-)

```
#### [PATCH V8 1/9] vhost: refine vhost and vringh kconfig
##### From: Jason Wang <jasowang@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11457161
Return-Path: <SRS0=cO5m=5K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A361E13A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Mar 2020 08:29:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 79A1C20777
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Mar 2020 08:29:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="NKhz9wso"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727301AbgCYI3F (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 25 Mar 2020 04:29:05 -0400
Received: from us-smtp-delivery-74.mimecast.com ([63.128.21.74]:28415 "EHLO
        us-smtp-delivery-74.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727275AbgCYI3F (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 25 Mar 2020 04:29:05 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1585124943;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=cQAMj9E7pnEO97gxazN0awVnwRs79iDcGQ6g5ZjNfoc=;
        b=NKhz9wsoP2r+XrbId9UXhxV9iY+hQ3OkG3YsAFSncWLLz9VPOdrjiprxPMRGgkP4zttVxi
        1kg+0dk4R9XEQjDKT+/4iZ45E+Em5qaqLfvf5U9XkiPvRkpkYe6J/oyvcLlHuLr9uHwWfK
        C6g2bsh7A9r4/pZjDY3eI2kmApGKZxI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-472-VuGpK1WMOQyXGxruIzwHmA-1; Wed, 25 Mar 2020 04:28:58 -0400
X-MC-Unique: VuGpK1WMOQyXGxruIzwHmA-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 34C9CDBA3;
        Wed, 25 Mar 2020 08:28:56 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-14-13.pek2.redhat.com [10.72.14.13])
        by smtp.corp.redhat.com (Postfix) with ESMTP id F0E371C947;
        Wed, 25 Mar 2020 08:28:06 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: mst@redhat.com, linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org
Cc: jgg@mellanox.com, maxime.coquelin@redhat.com,
        cunming.liang@intel.com, zhihong.wang@intel.com,
        rob.miller@broadcom.com, xiao.w.wang@intel.com,
        lingshan.zhu@intel.com, eperezma@redhat.com, lulu@redhat.com,
        parav@mellanox.com, kevin.tian@intel.com, stefanha@redhat.com,
        rdunlap@infradead.org, hch@infradead.org, aadam@redhat.com,
        jiri@mellanox.com, shahafs@mellanox.com, hanand@xilinx.com,
        mhabets@solarflare.com, gdawar@xilinx.com, saugatm@xilinx.com,
        vmireyno@marvell.com, Jason Wang <jasowang@redhat.com>
Subject: [PATCH V8 1/9] vhost: refine vhost and vringh kconfig
Date: Wed, 25 Mar 2020 16:27:03 +0800
Message-Id: <20200325082711.1107-2-jasowang@redhat.com>
In-Reply-To: <20200325082711.1107-1-jasowang@redhat.com>
References: <20200325082711.1107-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Currently, CONFIG_VHOST depends on CONFIG_VIRTUALIZATION. But vhost is
not necessarily for VM since it's a generic userspace and kernel
communication protocol. Such dependency may prevent archs without
virtualization support from using vhost.

To solve this, a dedicated vhost menu is created under drivers so
CONIFG_VHOST can be decoupled out of CONFIG_VIRTUALIZATION.

While at it, also squash Kconfig.vringh into vhost Kconfig file. This
avoids the trick of conditional inclusion from VOP or CAIF. Then it
will be easier to introduce new vringh users and common dependency for
both vringh and vhost.

Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 arch/arm/kvm/Kconfig         |  2 --
 arch/arm64/kvm/Kconfig       |  2 --
 arch/mips/kvm/Kconfig        |  2 --
 arch/powerpc/kvm/Kconfig     |  2 --
 arch/s390/kvm/Kconfig        |  4 ----
 arch/x86/kvm/Kconfig         |  4 ----
 drivers/Kconfig              |  2 ++
 drivers/misc/mic/Kconfig     |  4 ----
 drivers/net/caif/Kconfig     |  4 ----
 drivers/vhost/Kconfig        | 23 ++++++++++++++---------
 drivers/vhost/Kconfig.vringh |  6 ------
 11 files changed, 16 insertions(+), 39 deletions(-)
 delete mode 100644 drivers/vhost/Kconfig.vringh

```
