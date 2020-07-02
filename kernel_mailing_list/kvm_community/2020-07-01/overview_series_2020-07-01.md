#### [PATCH v13 01/11] KVM: x86: Include CET definitions for KVM test purpose
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11635605
Return-Path: <SRS0=UYgy=AM=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 259ED17D1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Jul 2020 08:06:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0C71C20775
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Jul 2020 08:06:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728545AbgGAIEZ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 1 Jul 2020 04:04:25 -0400
Received: from mga14.intel.com ([192.55.52.115]:2413 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728420AbgGAIEY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 1 Jul 2020 04:04:24 -0400
IronPort-SDR: 
 EQuRO9IEuwjQqllaAo0u+uUjjoZfwcgp52vqoPoVMX8oqhbrYe79sNt8mksF++NHyJgVo8EYI5
 WmnqunQQTcGw==
X-IronPort-AV: E=McAfee;i="6000,8403,9668"; a="145581826"
X-IronPort-AV: E=Sophos;i="5.75,299,1589266800";
   d="scan'208";a="145581826"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga005.jf.intel.com ([10.7.209.41])
  by fmsmga103.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 01 Jul 2020 01:04:14 -0700
IronPort-SDR: 
 mzze7toC3jy/njNgD0C5r2G7i7KN51Ncg/FUIQJ/VGZLtwgf3uyD8GtUFiz6aPiEgjP8/S09q3
 KHo7FeAbZ1zA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,299,1589266800";
   d="scan'208";a="455010225"
Received: from unknown (HELO local-michael-cet-test.sh.intel.com)
 ([10.239.159.128])
  by orsmga005.jf.intel.com with ESMTP; 01 Jul 2020 01:04:12 -0700
From: Yang Weijiang <weijiang.yang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        pbonzini@redhat.com, sean.j.christopherson@intel.com,
        jmattson@google.com
Cc: yu.c.zhang@linux.intel.com, Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH v13 01/11] KVM: x86: Include CET definitions for KVM test
 purpose
Date: Wed,  1 Jul 2020 16:04:01 +0800
Message-Id: <20200701080411.5802-2-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
In-Reply-To: <20200701080411.5802-1-weijiang.yang@intel.com>
References: <20200701080411.5802-1-weijiang.yang@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

These definitions are added by CET kernel patch and referenced by KVM,
if the CET KVM patches are tested without CET kernel patches, this patch
should be included.

Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>
---
 include/linux/kvm_host.h | 32 ++++++++++++++++++++++++++++++++
 1 file changed, 32 insertions(+)

```
#### [PATCH] kvmtool: arm64: Report missing support for 32bit guests
##### From: Suzuki K Poulose <suzuki.poulose@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Suzuki K Poulose <Suzuki.Poulose@arm.com>
X-Patchwork-Id: 11636563
Return-Path: <SRS0=UYgy=AM=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3994D13BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Jul 2020 14:20:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 21690207F9
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Jul 2020 14:20:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731622AbgGAOU1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 1 Jul 2020 10:20:27 -0400
Received: from foss.arm.com ([217.140.110.172]:44966 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1731324AbgGAOU0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 1 Jul 2020 10:20:26 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 60C5E30E;
        Wed,  1 Jul 2020 07:20:26 -0700 (PDT)
Received: from ewhatever.cambridge.arm.com (ewhatever.cambridge.arm.com
 [10.1.197.1])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 2242C3F73C;
        Wed,  1 Jul 2020 07:20:24 -0700 (PDT)
From: Suzuki K Poulose <suzuki.poulose@arm.com>
To: kvm@vger.kernel.org
Cc: kvmarm@lists.cs.columbia.edu, andre.przywara@arm.com,
        linux-arm-kernel@lists.infradead.org,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Will Deacon <will@kernel.org>,
        Sami Mujawar <sami.mujawar@arm.com>
Subject: [PATCH] kvmtool: arm64: Report missing support for 32bit guests
Date: Wed,  1 Jul 2020 15:20:02 +0100
Message-Id: <20200701142002.51654-1-suzuki.poulose@arm.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When the host doesn't support 32bit guests, the kvmtool fails
without a proper message on what is wrong. i.e,

 $ lkvm run -c 1 Image --aarch32
  # lkvm run -k Image -m 256 -c 1 --name guest-105618
  Fatal: Unable to initialise vcpu

Given that there is no other easy way to check if the host supports 32bit
guests, it is always good to report this by checking the capability, rather
than leaving the users to hunt this down by looking at the code!

After this patch:

 $ lkvm run -c 1 Image --aarch32
  # lkvm run -k Image -m 256 -c 1 --name guest-105695
  Fatal: 32bit guests are not supported

Cc: Will Deacon <will@kernel.org>
Reported-by: Sami Mujawar <sami.mujawar@arm.com>
Signed-off-by: Suzuki K Poulose <suzuki.poulose@arm.com>
Acked-by: Marc Zyngier <maz@kernel.org>
---
 arm/kvm-cpu.c | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [kvm-unit-tests PATCH] gitlab-ci.yml: Extend the lists of tests that we run with TCG
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11635995
Return-Path: <SRS0=UYgy=AM=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 210ED13BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Jul 2020 10:06:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 03A692073E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Jul 2020 10:06:27 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="C7pCUszr"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729716AbgGAKG0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 1 Jul 2020 06:06:26 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:20431 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1728755AbgGAKGZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 1 Jul 2020 06:06:25 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1593597984;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=SoDnJoSdaPt4sVuT7zf19dNUPvHCcGaRVDijteDFhQM=;
        b=C7pCUszr8ux+Wj5EJCDBULrH8fY5TH+WEESfBW2gTqln0LyrgZhFNyNVSAUDZNBz1dxfNM
        VMGUhDojYR9kJza2ELs91blmf4VUgm6c8D151KOH4ickdJQmlc1nwOFEpx2NIWg9uXRJfH
        +MOPjuhzWmU80Z7EddKnmsv/h3avEkU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-159-fhi-TPPvMS-vflC-XX8fXQ-1; Wed, 01 Jul 2020 06:06:22 -0400
X-MC-Unique: fhi-TPPvMS-vflC-XX8fXQ-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id E08FD1005513;
        Wed,  1 Jul 2020 10:06:21 +0000 (UTC)
Received: from thuth.com (ovpn-114-45.ams2.redhat.com [10.36.114.45])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 46F242B472;
        Wed,  1 Jul 2020 10:06:17 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Cc: Drew Jones <drjones@redhat.com>,
        David Hildenbrand <david@redhat.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        Cornelia Huck <cohuck@redhat.com>
Subject: [kvm-unit-tests PATCH] gitlab-ci.yml: Extend the lists of tests that
 we run with TCG
Date: Wed,  1 Jul 2020 12:06:15 +0200
Message-Id: <20200701100615.7975-1-thuth@redhat.com>
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Thank to the recent fixes, there are now quite a lot of additional 32-bit
x86 tests that we can run in the CI.
And thanks to the update to Fedora 32 (that introduced a newer version of
QEMU), there are now also some additional tests that we can run with TCG
for the other architectures.
Note that for arm/aarch64, we now also set the MAX_SMP to be able to run
SMP-tests with TCG in the single-threaded CI containers, too.

Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 Note: taskswitch2 for 32-bit x86 is still broken, and thus has not been
 added back again. It used to work with F30 ... maybe it's a QEMU regression?

 .gitlab-ci.yml | 24 +++++++++++++++---------
 1 file changed, 15 insertions(+), 9 deletions(-)

```
#### [kvm-unit-tests PATCH] scripts: Fix the check whether testname is in the only_tests list
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11635639
Return-Path: <SRS0=UYgy=AM=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1557392A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Jul 2020 08:38:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E9BFF2074D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Jul 2020 08:38:01 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="D9LSLefO"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728683AbgGAIiA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 1 Jul 2020 04:38:00 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:25782 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726670AbgGAIiA (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 1 Jul 2020 04:38:00 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1593592679;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=QahaNqoJpNuE2oXc7Lbni+jgHUbCC+VzOS4RvDj9bVU=;
        b=D9LSLefOI98MKj02ej8i6tuQ2hulqH44JmY/IcNAy9eMbvVgw9cfQXrJSUQhrXs1DTG4F7
        DrI5NPG975bJd2/qFxY6rFpudI/FuYibKmm4fg8mWxryuuEbsv5gI59TvckS1QFFdTGpD8
        hOSYzb47ev+hpd0fIYt2GAqDEUXQggE=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-35-ybOFw22LP5SCzkSRCEONrA-1; Wed, 01 Jul 2020 04:37:57 -0400
X-MC-Unique: ybOFw22LP5SCzkSRCEONrA-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 0AA341902EA1
        for <kvm@vger.kernel.org>; Wed,  1 Jul 2020 08:37:57 +0000 (UTC)
Received: from thuth.com (ovpn-114-45.ams2.redhat.com [10.36.114.45])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 01CC68ACE9;
        Wed,  1 Jul 2020 08:37:55 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Cc: Drew Jones <drjones@redhat.com>
Subject: [kvm-unit-tests PATCH] scripts: Fix the check whether testname is in
 the only_tests list
Date: Wed,  1 Jul 2020 10:37:53 +0200
Message-Id: <20200701083753.31366-1-thuth@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When you currently run

 ./run_tests.sh ioapic-split

the kvm-unit-tests run scripts do not only execute the "ioapic-split"
test, but also the "ioapic" test, which is quite surprising. This
happens because we use "grep -w" for checking whether a test should
be run or not - and "grep -w" does not consider the "-" character as
part of a word.

To fix the issue, convert the dash into an underscore character before
running "grep -w".

Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 scripts/runtime.bash | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH kvm-unit-tests] scripts: Fix the check whether testname is in the only_tests list
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11635953
Return-Path: <SRS0=UYgy=AM=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 75F1B13B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Jul 2020 09:46:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5B61D2073E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Jul 2020 09:46:40 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="Y/0t9cfT"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729578AbgGAJqj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 1 Jul 2020 05:46:39 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:34908 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729236AbgGAJqi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 1 Jul 2020 05:46:38 -0400
Received: from mail-ej1-x644.google.com (mail-ej1-x644.google.com
 [IPv6:2a00:1450:4864:20::644])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id A1BEDC061755
        for <kvm@vger.kernel.org>; Wed,  1 Jul 2020 02:46:38 -0700 (PDT)
Received: by mail-ej1-x644.google.com with SMTP id n26so9909968ejx.0
        for <kvm@vger.kernel.org>; Wed, 01 Jul 2020 02:46:38 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=B/lOuMjqn37ghAr7+CYcTtdGMa1UHjGi1TO5Py8wL70=;
        b=Y/0t9cfTAhD5w4JO0HRkyRv8XzijM4h2KFfV9kdtY0PghVwktHkVxu9su6Qq9v7CMv
         TkwGfShuqboacIAJj7vY8r9fDOKBBetGn8TskxBirGEyBaB0PPmSvjh0ZWP5lMaMYDMR
         U9mASouL9uR9ZlGI70LmwTJJMQnHojuSi2foB28bAILDe1yu/a7B4EX4LajNm5XQrzgO
         fYiX8XuTquvYSvXXTNO6yTs86jkYZ3jkAWsvBWN/TQrnxDrjUrbwVc8c5YV8/A5K6XyM
         HLcKNLOgQvX1CXrI8+YxkR9qTudaCiTw8TUtEYtK2aQrIEPS4notcBOHTMnoLUFu/Ki9
         aX0w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :mime-version:content-transfer-encoding;
        bh=B/lOuMjqn37ghAr7+CYcTtdGMa1UHjGi1TO5Py8wL70=;
        b=H0VlcpIi6jbKJhNZ2iW/ZK2EKuaG28QwPV6qajcFk/V14Gf78q40qt3c7qrCx3chnN
         g3ApNvOMSU+ZqUqLq4SPyVKRTXNozUPKX3nfyHeavW4lZz5MNqxkMtAMzNnoviJikLyJ
         oYuGfyZzsUtx9CDZvoghBpZBv8O6qQ75ogbeWS3wa7iw4Y9P2hauJ0nbMRaVXi08J33e
         KNqDCb5yeJBy+Hzmn545lxOh8XRPA7TXP0U5sdevjykb4z+rd1hhWJP5/DLRYptbDa8c
         NJG1lu/7TpRLQ5NdcjrFFCnqQN9MzGIbj7SJMD8wM9xwU0ci6Np+F7uWW+sXuiVLnjZo
         pcOw==
X-Gm-Message-State: AOAM5321QgqXEHW3Zry9+x2o6W92iu3/Njp8cLMvEZddpmpHVLfhjxK8
        mKhYdwM6/ykiWbYutDnaPVXFwm/Oq0U=
X-Google-Smtp-Source: 
 ABdhPJwN1JjFPJq3YM2HXQnaRtEDyRN8PQmdR87nUpn5ERx74WRAgRUCqaF10BywWEV7Eo7osvgbeA==
X-Received: by 2002:a17:906:c10f:: with SMTP id
 do15mr23256499ejc.249.1593596797121;
        Wed, 01 Jul 2020 02:46:37 -0700 (PDT)
Received: from donizetti.lan ([2001:b07:6468:f312:1142:70d6:6b9b:3cd1])
        by smtp.gmail.com with ESMTPSA id
 mf24sm4185759ejb.58.2020.07.01.02.46.36
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 01 Jul 2020 02:46:36 -0700 (PDT)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Cc: Thomas Huth <thuth@redhat.com>
Subject: [PATCH kvm-unit-tests] scripts: Fix the check whether testname is in
 the only_tests list
Date: Wed,  1 Jul 2020 11:46:35 +0200
Message-Id: <20200701094635.19491-1-pbonzini@redhat.com>
X-Mailer: git-send-email 2.25.4
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When you currently run

  ./run_tests.sh ioapic-split

the kvm-unit-tests run scripts do not only execute the "ioapic-split"
test, but also the "ioapic" test, which is quite surprising. This
happens because we use "grep -w" for checking whether a test should
be run or not.  Because "grep -w" does not consider the "-" character as
part of a word, "ioapic" successfully matches against "ioapic-split".

To fix the issue, use spaces as the only delimiter when running "grep",
removing the problematic "-w" flag from the invocation.

Reported-by: Thomas Huth <thuth@redhat.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Tested-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
---
 scripts/runtime.bash | 11 ++++++++---
 1 file changed, 8 insertions(+), 3 deletions(-)

```
#### [kvm-unit-tests PATCH] x86: realmode: fix serial_init()
##### From: Nadav Amit <namit@vmware.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nadav Amit <namit@vmware.com>
X-Patchwork-Id: 11637131
Return-Path: <SRS0=UYgy=AM=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 624736C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Jul 2020 19:33:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 505C620760
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Jul 2020 19:33:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726030AbgGATdG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 1 Jul 2020 15:33:06 -0400
Received: from ex13-edg-ou-001.vmware.com ([208.91.0.189]:9757 "EHLO
        EX13-EDG-OU-001.vmware.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725771AbgGATdF (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 1 Jul 2020 15:33:05 -0400
Received: from sc9-mailhost3.vmware.com (10.113.161.73) by
 EX13-EDG-OU-001.vmware.com (10.113.208.155) with Microsoft SMTP Server id
 15.0.1156.6; Wed, 1 Jul 2020 12:33:03 -0700
Received: from sc2-haas01-esx0118.eng.vmware.com
 (sc2-haas01-esx0118.eng.vmware.com [10.172.44.118])
        by sc9-mailhost3.vmware.com (Postfix) with ESMTP id 429F1407A8;
        Wed,  1 Jul 2020 12:33:05 -0700 (PDT)
From: Nadav Amit <namit@vmware.com>
To: Paolo Bonzini <pbonzini@redhat.com>
CC: <kvm@vger.kernel.org>, Nadav Amit <namit@vmware.com>
Subject: [kvm-unit-tests PATCH] x86: realmode: fix serial_init()
Date: Wed, 1 Jul 2020 12:30:45 -0700
Message-ID: <20200701193045.31247-1-namit@vmware.com>
X-Mailer: git-send-email 2.17.1
MIME-Version: 1.0
Received-SPF: None (EX13-EDG-OU-001.vmware.com: namit@vmware.com does not
 designate permitted sender hosts)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In some setups serial output from the real-mode tests is corrupted.

I do not know the serial port initialization code well, but the
protected mode initialization code is different than the real-mode code.
Using the protected mode serial port initialization fixes the problem.

Keeping the tradition of code duplication between real-mode and
protected mode, this patch copies the missing initialization into
real-mode serial port initialization.

Signed-off-by: Nadav Amit <namit@vmware.com>
---
 x86/realmode.c | 9 +++++++++
 1 file changed, 9 insertions(+)

```
#### [PATCH 1/5] PCI: add Intel QuickAssist device IDs
##### From: Giovanni Cabiddu <giovanni.cabiddu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Giovanni Cabiddu <giovanni.cabiddu@intel.com>
X-Patchwork-Id: 11636107
Return-Path: <SRS0=UYgy=AM=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9594D92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Jul 2020 11:03:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8760120772
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Jul 2020 11:03:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730196AbgGALDg (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 1 Jul 2020 07:03:36 -0400
Received: from mga17.intel.com ([192.55.52.151]:29868 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729791AbgGALDe (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 1 Jul 2020 07:03:34 -0400
IronPort-SDR: 
 m1ynp8YAK7Ao67z4jJsfZGPIThTCR6seyS1E/qHUP7IKxq0QuNAujvWrIIjJkxVUnpouprppM3
 icNmArN29Puw==
X-IronPort-AV: E=McAfee;i="6000,8403,9668"; a="126632423"
X-IronPort-AV: E=Sophos;i="5.75,300,1589266800";
   d="scan'208";a="126632423"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by fmsmga107.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 01 Jul 2020 04:03:33 -0700
IronPort-SDR: 
 Wf6clD5dgBtr4bWzB3CweN+zOozGK0xntJZ5st57PL/e2CDlmMh5fhudcqyamf09gKk4tbkrjz
 8qXoVp8zBxlw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,300,1589266800";
   d="scan'208";a="425557251"
Received: from silpixa00400314.ir.intel.com (HELO
 silpixa00400314.ger.corp.intel.com) ([10.237.222.51])
  by orsmga004.jf.intel.com with ESMTP; 01 Jul 2020 04:03:30 -0700
From: Giovanni Cabiddu <giovanni.cabiddu@intel.com>
To: alex.williamson@redhat.com, herbert@gondor.apana.org.au
Cc: cohuck@redhat.com, nhorman@redhat.com, vdronov@redhat.com,
        bhelgaas@google.com, mark.a.chambers@intel.com,
        gordon.mcfadden@intel.com, ahsan.atta@intel.com,
        qat-linux@intel.com, kvm@vger.kernel.org,
        linux-crypto@vger.kernel.org, linux-pci@vger.kernel.org,
        linux-kernel@vger.kernel.org,
        Giovanni Cabiddu <giovanni.cabiddu@intel.com>
Subject: [PATCH 1/5] PCI: add Intel QuickAssist device IDs
Date: Wed,  1 Jul 2020 12:02:58 +0100
Message-Id: <20200701110302.75199-2-giovanni.cabiddu@intel.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200701110302.75199-1-giovanni.cabiddu@intel.com>
References: <20200701110302.75199-1-giovanni.cabiddu@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add device IDs for the following Intel QuickAssist devices: DH895XCC,
C3XXX and C62X.

The defines in this patch are going to be referenced in two independent
drivers, qat and vfio-pci.

Signed-off-by: Giovanni Cabiddu <giovanni.cabiddu@intel.com>
---
 include/linux/pci_ids.h | 6 ++++++
 1 file changed, 6 insertions(+)

```
#### [PATCH] vfio/pci: Add Intel X550 to hidden INTx devicesFrom: Alex Williamson <alex.williamson@redhat.com>
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 11637253
Return-Path: <SRS0=UYgy=AM=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 74BDB618
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Jul 2020 21:02:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 544A320870
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Jul 2020 21:02:42 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="IPTjrwRL"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727062AbgGAVCl (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 1 Jul 2020 17:02:41 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:45634 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1725535AbgGAVCl (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 1 Jul 2020 17:02:41 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1593637360;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=/2cNlIlhLsfre0+HjP1RIAKjqNYYQUIp8pAZWmFwfi4=;
        b=IPTjrwRLKgX5vGqlQUHuEKWboqsYd1OItQweRMqzPAZoQHM7+UQ2dMuOgu5AvXWaV4J4rc
        UbbM/T7uBhNK2JSYlFTyLpBZeKM0PUs+bqVnfsl4N7xy9u0x6HFrijVLMGUIoBbC2s8Bq9
        iPp4/z6RGVp6FjkmqrJPo+Ibl0/IfTY=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-427-Zr6jlFD3OeGcr5l350Wb2g-1; Wed, 01 Jul 2020 17:02:38 -0400
X-MC-Unique: Zr6jlFD3OeGcr5l350Wb2g-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 55E07186A200;
        Wed,  1 Jul 2020 21:02:37 +0000 (UTC)
Received: from gimli.home (ovpn-112-156.phx2.redhat.com [10.3.112.156])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 3654A60CD1;
        Wed,  1 Jul 2020 21:02:34 +0000 (UTC)
Subject: [PATCH] vfio/pci: Add Intel X550 to hidden INTx devices
From: Alex Williamson <alex.williamson@redhat.com>
To: alex.williamson@redhat.com
Cc: Jesse Brandeburg <jesse.brandeburg@intel.com>,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        linux-pci@vger.kernel.org
Date: Wed, 01 Jul 2020 15:02:33 -0600
Message-ID: <159363734524.19359.5271945196793749675.stgit@gimli.home>
User-Agent: StGit/0.19-dirty
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Intel document 333717-008, "Intel® Ethernet Controller X550
Specification Update", version 2.7, dated June 2020, includes errata
#22, added in version 2.1, May 2016, indicating X550 NICs suffer from
the same implementation deficiency as the 700-series NICs:

"The Interrupt Status bit in the Status register of the PCIe
 configuration space is not implemented and is not set as described
 in the PCIe specification."

Without the interrupt status bit, vfio-pci cannot determine when
these devices signal INTx.  They are therefore added to the nointx
quirk.

Cc: Jesse Brandeburg <jesse.brandeburg@intel.com>
Signed-off-by: Alex Williamson <alex.williamson@redhat.com>
---
 drivers/vfio/pci/vfio_pci.c |    2 ++
 1 file changed, 2 insertions(+)

```
