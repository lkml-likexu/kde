#### [PATCH v2 1/2] KVM: Documentation: Update fast page fault for indirect sp
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11422085
Return-Path: <SRS0=eotC=4W=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3E18418B8
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Mar 2020 15:57:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 17C5520848
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Mar 2020 15:57:21 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="HX5orCBV"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727026AbgCEP5R (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Mar 2020 10:57:17 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:46459 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726998AbgCEP5R (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Mar 2020 10:57:17 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1583423836;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=giheljeQP6Uu0Yz/rFBlh12QkzN9q9BUOHVrPPrqkx8=;
        b=HX5orCBVqSUEiQcESWb3nSt7EB5GfI+WGL3dewtZSp/970ljwfL6tN/OwezSZmee9gBb2F
        r+3cpk75oYmd6Jb2CdmFeuzPt05tUlkN4mjXyC8vx75jqYsOO6M5V5okJg4vFWl7H1C/R/
        F5czHRhS6v6xsjOBND3BC6xbQKKDZkY=
Received: from mail-qv1-f72.google.com (mail-qv1-f72.google.com
 [209.85.219.72]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-347-TyHK2V3BPEKePur92QHmXA-1; Thu, 05 Mar 2020 10:57:15 -0500
X-MC-Unique: TyHK2V3BPEKePur92QHmXA-1
Received: by mail-qv1-f72.google.com with SMTP id s2so3271709qvt.16
        for <kvm@vger.kernel.org>; Thu, 05 Mar 2020 07:57:15 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=giheljeQP6Uu0Yz/rFBlh12QkzN9q9BUOHVrPPrqkx8=;
        b=I/E9j7TWVu4xrENqUyNzbnsBxvZIEo7qM5zTcBwyBnNH8y/uL1fy6QJOYm2eGXLXh5
         6KXhcPuXfLeUG7mcbjcmHjHv3jqvXNAt6TCXsK8vV5TpeEu29nJnPCvCWwGFRavnOuGQ
         QgU4cr4w12XEFIlYb1Q5dP8tdAQytDAMY1zKlUiZ0ANJAR0jQXJ//ioNyGPNDuPiexcD
         RCAp/QgIG/N0jUhbrHqPQytrI1ogFjRtXNk9w0KeIYI10NAA8xpTy9kbyQTPhJ96Xq9u
         KXGPuOxoNcaj56IqI8RCHREN2uWfn8n1TBDjawHm5OnPz9DQbEMVAAhLqAMpkwOdhhH9
         74BQ==
X-Gm-Message-State: ANhLgQ3PQNKckOIrhd1Vv+MyM6iktoJipfMr9h+rBRVCV8QLkl5ZQ3qj
        8RufDL1MBX71gcNqaZopt492rvl3q6lN+HYidsx7Rgosy/JXLJyht/CVoL7gc9U/474DOF5qV9m
        SvxoYF0JsUgAe
X-Received: by 2002:a05:620a:1278:: with SMTP id
 b24mr8060002qkl.387.1583423834576;
        Thu, 05 Mar 2020 07:57:14 -0800 (PST)
X-Google-Smtp-Source: 
 ADFU+vuS9VXeOpu9/W83Z1y6Y24APvGXa7o2yN6VxlQqagLVu9bnEMeqGkR1oGxJCIotDVDEQlOaQA==
X-Received: by 2002:a05:620a:1278:: with SMTP id
 b24mr8059984qkl.387.1583423834350;
        Thu, 05 Mar 2020 07:57:14 -0800 (PST)
Received: from xz-x1.redhat.com ([2607:9880:19c0:32::2])
        by smtp.gmail.com with ESMTPSA id
 c13sm10172236qtv.37.2020.03.05.07.57.13
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 05 Mar 2020 07:57:13 -0800 (PST)
From: Peter Xu <peterx@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: linmiaohe@huawei.com, Paolo Bonzini <pbonzini@redhat.com>,
        peterx@redhat.com
Subject: [PATCH v2 1/2] KVM: Documentation: Update fast page fault for
 indirect sp
Date: Thu,  5 Mar 2020 10:57:08 -0500
Message-Id: <20200305155709.118503-2-peterx@redhat.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200305155709.118503-1-peterx@redhat.com>
References: <20200305155709.118503-1-peterx@redhat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

gfn_to_pfn_atomic() is not used anywhere.  Before dropping it,
reorganize the locking document to state the fact that we're not
enabling fast page fault for indirect sps.  The previous wording is
confusing that it seems we have implemented it however it's not.

Signed-off-by: Peter Xu <peterx@redhat.com>
---
 Documentation/virt/kvm/locking.rst | 9 ++++-----
 1 file changed, 4 insertions(+), 5 deletions(-)

```
#### [PATCH 1/4] KVM: nSVM: do not change host intercepts while nested VM is running
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11421495
Return-Path: <SRS0=eotC=4W=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BE57C138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Mar 2020 10:14:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9BE7F21556
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Mar 2020 10:14:01 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="k7VCsKw3"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727070AbgCEKNz (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Mar 2020 05:13:55 -0500
Received: from mail-wr1-f68.google.com ([209.85.221.68]:45595 "EHLO
        mail-wr1-f68.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725816AbgCEKNy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Mar 2020 05:13:54 -0500
Received: by mail-wr1-f68.google.com with SMTP id v2so6233311wrp.12;
        Thu, 05 Mar 2020 02:13:52 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=N8hO5OsCpxWuOROH3axUS5MYcS8LdG5MKkBcvb8lPiI=;
        b=k7VCsKw36KHwV++K8F4b0/Ji76zJCnV+jm7l6g7L9fch4EzkCd0ZmEZKIxW/5LxowI
         r9TYDLVpBcHcNM3xoHfCHMWaAB1ylrVOZ4wrrtLToqQYWDVzubYWqM14kePDG4F/j9sy
         LJgA0n5tLzcvKZGNtTpnmw4F6bEyMaqus/IpJh6lNVyQHgSDKZj1NyG2uHhXlprIOzgB
         TY61lVEP6KoT7oKBgbq6qbIM8fLGZSAwQ2Z56BrWAY1vEav4BiBzmMEXkZ0MbWSV0w7Z
         ei+Y0KwbJ/jAuB2XwzDzHkrdo8S8JK7Dawv1uca/0m87PZgx1xls6hq+2h726WB47mun
         Py/Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :in-reply-to:references;
        bh=N8hO5OsCpxWuOROH3axUS5MYcS8LdG5MKkBcvb8lPiI=;
        b=qfcW6+kDj/w9cWSCn0DVrvsOOuyzYxISFlYCZUliCftkFKVEDEdFgAHTdRkvadxgOP
         Q2frFncXUWJHaTtUrOEKcfYsHPssa4iwYzt/DmV6X9/vJJcYoxY1eb9ihy6Ao/S3gqyu
         18Y2sCpv6H/f2bGLfJVqkxLgCIsarXXLZBVvU1fQ3rMT0+h90qzN4ilBvIPoYlPuMU6k
         uB5odjVYHafES/8fLhSjMTzizVtnTz8eTDRpX77ZMaujoiAoHKuFRzPirGACzCIG8Lsj
         4kJ+5LE2fhr8NwHffNSSlsWwfsXHVabuUiPX6XqhiLfSiuGWWljwIQ6FbkIVypEc+Gig
         kIYw==
X-Gm-Message-State: ANhLgQ1H9mZJcFs8fAQ4sXC+/reTouRVDM0ZoufgPLVxHzJMGNIKeDhe
        kIb0wQ3N7wF01NbOT5/cDfRuqlrp
X-Google-Smtp-Source: 
 ADFU+vu1GR7uwsHOWLQOZhzN5rk63Bcdi98Dk/283VeBS36I6xrBrZLZ4VLn8guP/UUC8RmFGJ94zA==
X-Received: by 2002:adf:a50b:: with SMTP id i11mr10151797wrb.60.1583403231224;
        Thu, 05 Mar 2020 02:13:51 -0800 (PST)
Received: from 640k.localdomain.com ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 p15sm8331066wma.40.2020.03.05.02.13.50
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 05 Mar 2020 02:13:50 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: cavery@redhat.com, vkuznets@redhat.com, jan.kiszka@siemens.com,
        wei.huang2@amd.com
Subject: [PATCH 1/4] KVM: nSVM: do not change host intercepts while nested VM
 is running
Date: Thu,  5 Mar 2020 11:13:44 +0100
Message-Id: <1583403227-11432-2-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1583403227-11432-1-git-send-email-pbonzini@redhat.com>
References: <1583403227-11432-1-git-send-email-pbonzini@redhat.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Instead of touching the host intercepts so that the bitwise OR in
recalc_intercepts just works, mask away uninteresting intercepts
directly in recalc_intercepts.

This is cleaner and keeps the logic in one place even for intercepts
that can change even while L2 is running.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/svm.c | 31 ++++++++++++++++++-------------
 1 file changed, 18 insertions(+), 13 deletions(-)

```
#### [RFC PATCH 1/1] kvm: selftests: Add TEST_FAIL macro
##### From: Wainer dos Santos Moschetta <wainersm@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wainer dos Santos Moschetta <wainersm@redhat.com>
X-Patchwork-Id: 11422423
Return-Path: <SRS0=eotC=4W=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D4CD7174A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Mar 2020 17:25:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B537820726
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Mar 2020 17:25:59 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="JhhviSFk"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727745AbgCERZ6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Mar 2020 12:25:58 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:59110 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727565AbgCERZ6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Mar 2020 12:25:58 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1583429157;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:in-reply-to:in-reply-to:references:references;
        bh=jKNSxLmMS1+TC7wrcKR5f9MZfVifwBf0zoemzoIpDZ4=;
        b=JhhviSFkfGfaSZxXHeKyrvNMExflgbqFH+42oKT3viAMLKRji27AXnHXDcmHs43L9dueMB
        aD83F77rXSdmOYpywvwVgzpsWeAVWo6xBejYKxqJDwDiJ/hDThwpBeUhaEG5INficqB0vi
        QBnbNUVTCmYKcSpsEBukYejSSBmenCg=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-160-3ZC_uy4VOi-n-Fq54ncYwQ-1; Thu, 05 Mar 2020 12:25:54 -0500
X-MC-Unique: 3ZC_uy4VOi-n-Fq54ncYwQ-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 8D0F8800D50;
        Thu,  5 Mar 2020 17:25:50 +0000 (UTC)
Received: from localhost.localdomain (ovpn-116-124.gru2.redhat.com
 [10.97.116.124])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 98B505C290;
        Thu,  5 Mar 2020 17:25:46 +0000 (UTC)
From: Wainer dos Santos Moschetta <wainersm@redhat.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: shuah@kernel.org, tglx@linutronix.de, thuth@redhat.com,
        sean.j.christopherson@intel.com, linux-kselftest@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [RFC PATCH 1/1] kvm: selftests: Add TEST_FAIL macro
Date: Thu,  5 Mar 2020 14:25:32 -0300
Message-Id: <20200305172532.9360-2-wainersm@redhat.com>
In-Reply-To: <20200305172532.9360-1-wainersm@redhat.com>
References: <20200305172532.9360-1-wainersm@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Some tests/utilities use the TEST_ASSERT(false, ...) pattern to
indicate a failure and stop execution.

This change introduces the TEST_FAIL macro which is a wrap around
TEST_ASSERT(false, ...) and so provides a direct alternative for
failing a test.

Signed-off-by: Wainer dos Santos Moschetta <wainersm@redhat.com>
---
 tools/testing/selftests/kvm/dirty_log_test.c             | 7 +++----
 tools/testing/selftests/kvm/include/test_util.h          | 3 +++
 tools/testing/selftests/kvm/x86_64/cr4_cpuid_sync_test.c | 4 ++--
 3 files changed, 8 insertions(+), 6 deletions(-)

```
#### [PATCH kvm-unit-tests] svm: allow specifying the tests to be run
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11421437
Return-Path: <SRS0=eotC=4W=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 966C814B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Mar 2020 09:34:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 76C2120870
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Mar 2020 09:34:38 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="ALrNrWgk"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726968AbgCEJeh (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Mar 2020 04:34:37 -0500
Received: from mail-wm1-f66.google.com ([209.85.128.66]:39896 "EHLO
        mail-wm1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725897AbgCEJeh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Mar 2020 04:34:37 -0500
Received: by mail-wm1-f66.google.com with SMTP id j1so4900663wmi.4
        for <kvm@vger.kernel.org>; Thu, 05 Mar 2020 01:34:35 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:subject:date:message-id;
        bh=inOOEeU8s4MrMsZvPiN0++tfetTMGOEO2+eeER8zsek=;
        b=ALrNrWgkNd2p5pFR/ZIwZChNseSuz5G6+cTUdZEBl0e5qwYCns7kkQ4lA1WDRdTI8V
         fkg0yvz8eaqn5tSBTg4sKjhcR7XA/fPGCW3cHM+4xCkNmYUL4HfsJYj/V5lpODqqNfce
         r4eMCyhA2xKJDmoNY7vUuh9uqC5LOFqXkMA2dZkymhuQVfmvBkXEkISw6zGzp9DFzi5Q
         s/JWjSH0U9dhTa5yPqjv6r+3Gl3H01ZLldsdLKB1oBjWVjx4hzDjq2pfCto+lVNV44Xe
         Skz9XUh/QvKiGJWwjDUGp6J073XZjVLX4c4nDU9Qa6Gq2FFe4gxHp+4lojIxu4N6VbR4
         l4iw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:subject:date:message-id;
        bh=inOOEeU8s4MrMsZvPiN0++tfetTMGOEO2+eeER8zsek=;
        b=QNh/mBujWalplkMO11nMrajgc823ZRgcPLpmmIn29cp/DlcN2o/XAlgkqietpuxLK5
         nUfzNqw3R7zbo8id6imF3ZzHLpXI0fqs1iQL/hyjEQJZiDp0qQ0JKFZiIf5MdlRbmXH0
         unIBP3M6+KN4YsJ8RgLf/Omu+cnpC2YdU06qtXFao+sueif5WIrX/2aJMzZhyaYfV1YH
         whCjPPtvAogUhl+G1KCwO/Clo6hC4wXTdkad0hl/ZCUO4pl+IVF3esjjX+S4lte+KTgC
         FL1GJr+DebWyGs7yA53YAcuXZyt4nTcltVl8Jpv0G9S1QRR8aM4FavMmKtQZiCRrGswB
         wVEQ==
X-Gm-Message-State: ANhLgQ3l3GnJ9y9xm31TW3IogYDanBN4VO7+ARmGmiZQFnds9sEpFa9N
        7LwsP7Uqk8v2G5J0H+mPD9UsK6SC
X-Google-Smtp-Source: 
 ADFU+vvFrZaXLFGUv+geLRkR53ie855V/El8x2mh8raI6hNczTUG77r0M65sAnmuFtAWnwuN6En9PQ==
X-Received: by 2002:a05:600c:2942:: with SMTP id
 n2mr8270323wmd.87.1583400874687;
        Thu, 05 Mar 2020 01:34:34 -0800 (PST)
Received: from 640k.localdomain.com ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 i7sm28323587wro.87.2020.03.05.01.34.33
        for <kvm@vger.kernel.org>
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 05 Mar 2020 01:34:34 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Subject: [PATCH kvm-unit-tests] svm: allow specifying the tests to be run
Date: Thu,  5 Mar 2020 10:34:32 +0100
Message-Id: <1583400872-56657-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Copy over the test_wanted machinery from vmx.c.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 x86/svm.c | 46 +++++++++++++++++++++++++++++++++++++++++++++-
 1 file changed, 45 insertions(+), 1 deletion(-)

```
#### [PATCH v2 1/2] KVM: VMX: rename 'kvm_area' to 'vmxon_region'
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11422463
Return-Path: <SRS0=eotC=4W=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9566992A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Mar 2020 18:37:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 76349208C3
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Mar 2020 18:37:46 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="DpQXySBb"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727000AbgCEShg (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Mar 2020 13:37:36 -0500
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:47745 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1725991AbgCEShf (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 5 Mar 2020 13:37:35 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1583433454;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=y2yWNaYqjJ/RvKkVVduCbhM3C1I4Zkz6logIvpDXjRI=;
        b=DpQXySBbj5+q95FBbtMX5dH5e2K6asPAS1PJWYArG4SHh7JsOtn3iZEFYfx9nBYEcDQ/Mu
        81nT1u13M8Mh1JJgc/HaYkyLL1scbSK+DWajqImVUGBDt4CcbWZ4vJA2roWvom2Yqi36cX
        F/G00qKsdxpviD70lTNfPeOn0An0avE=
Received: from mail-wm1-f72.google.com (mail-wm1-f72.google.com
 [209.85.128.72]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-62-fj3C1rRJOTiNnTfqlayXpQ-1; Thu, 05 Mar 2020 13:37:32 -0500
X-MC-Unique: fj3C1rRJOTiNnTfqlayXpQ-1
Received: by mail-wm1-f72.google.com with SMTP id g26so1891078wmk.6
        for <kvm@vger.kernel.org>; Thu, 05 Mar 2020 10:37:32 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=y2yWNaYqjJ/RvKkVVduCbhM3C1I4Zkz6logIvpDXjRI=;
        b=gAnV8D0ML75LFBHrgDrwPbLej6630R/4ZU1MfJ0e2WZMr0yrfI7n12hzQrYDSbsfmE
         SZ/YM0/6TYhd/qAFLXqTQWAixjImFfFVtvOjNWMM19IzI1XlQamqerqxlKAcvG5jJNl/
         s27pkSPIhQL2MhC2NXFAMGOnjxeYj3PM0VLgSDPFK9brdrHoolrjS2b8zNiEff5oXrFj
         ke8RIdvJSEgNKqSiSa84+d25a1tQzADbGKhS7L8ymN+Xi3qXOjzhGAjGkwYWqYDSA3Wf
         E7HcVG6Vg5N1uC9WZTC3okxGq/ewGF4C4oeDLIiFbYL7LE9cOoh6oB0UwpCqrkrnG17z
         fJoA==
X-Gm-Message-State: ANhLgQ1njeR1dOy0Vvos3lZlnZxdDjpEXHjgf0ZiiURtx259YtAyjkWE
        rPQpYHzpVunN4G/szaqwysEatIqKNjG7tu/M7/zQXhagi/v1wr4LtjMdDT76IkfUOXZkTQkoot9
        iew951HxoqL7L
X-Received: by 2002:a5d:4805:: with SMTP id l5mr251440wrq.11.1583433451434;
        Thu, 05 Mar 2020 10:37:31 -0800 (PST)
X-Google-Smtp-Source: 
 ADFU+vt5yUT+iVGTGcKSZmbdeAb5G5VOmuV4IHK9ltTcOTR1wb/CGf1O1/ALTCR0TuslpOqF3DIkKg==
X-Received: by 2002:a5d:4805:: with SMTP id l5mr251423wrq.11.1583433451243;
        Thu, 05 Mar 2020 10:37:31 -0800 (PST)
Received: from vitty.brq.redhat.com (g-server-2.ign.cz. [91.219.240.2])
        by smtp.gmail.com with ESMTPSA id
 u17sm9369121wmj.47.2020.03.05.10.37.29
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 05 Mar 2020 10:37:30 -0800 (PST)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Jim Mattson <jmattson@google.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2 1/2] KVM: VMX: rename 'kvm_area' to 'vmxon_region'
Date: Thu,  5 Mar 2020 19:37:24 +0100
Message-Id: <20200305183725.28872-2-vkuznets@redhat.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200305183725.28872-1-vkuznets@redhat.com>
References: <20200305183725.28872-1-vkuznets@redhat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The name 'kvm_area' is misleading (as we have way too many areas which are
KVM related), what alloc_kvm_area()/free_kvm_area() functions really do is
allocate/free VMXON region for all CPUs. Rename accordingly.

No functional change intended.

Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/vmx/vmx.c | 10 +++++-----
 1 file changed, 5 insertions(+), 5 deletions(-)

```
#### [PATCH] KVM: VMX: Use wrapper macro ~RMODE_GUEST_OWNED_EFLAGS_BITS directly
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11421107
Return-Path: <SRS0=eotC=4W=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CB004139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Mar 2020 02:32:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B5C2820838
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Mar 2020 02:32:47 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725919AbgCECco (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 4 Mar 2020 21:32:44 -0500
Received: from szxga04-in.huawei.com ([45.249.212.190]:11144 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1725810AbgCECco (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 4 Mar 2020 21:32:44 -0500
Received: from DGGEMS410-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id C5C67A2B9C0A401CC778;
        Thu,  5 Mar 2020 10:32:40 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS410-HUB.china.huawei.com
 (10.3.19.210) with Microsoft SMTP Server id 14.3.439.0; Thu, 5 Mar 2020
 10:32:32 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <jmattson@google.com>, <joro@8bytes.org>, <tglx@linutronix.de>,
        <mingo@redhat.com>, <bp@alien8.de>, <hpa@zytor.com>
CC: <linmiaohe@huawei.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <x86@kernel.org>
Subject: [PATCH] KVM: VMX: Use wrapper macro ~RMODE_GUEST_OWNED_EFLAGS_BITS
 directly
Date: Thu, 5 Mar 2020 10:35:31 +0800
Message-ID: <1583375731-18219-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

(X86_EFLAGS_IOPL | X86_EFLAGS_VM) indicates the eflag bits that can not be
owned by realmode guest, i.e. ~RMODE_GUEST_OWNED_EFLAGS_BITS. Use wrapper
macro directly to make it clear and also improve readability.

Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
---
 arch/x86/kvm/vmx/vmx.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH v2 1/7] KVM: x86: Trace the original requested CPUID function in kvm_cpuid()
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11421039
Return-Path: <SRS0=eotC=4W=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 14596174A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Mar 2020 01:35:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id F40532146E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Mar 2020 01:35:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725991AbgCEBel (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 4 Mar 2020 20:34:41 -0500
Received: from mga03.intel.com ([134.134.136.65]:31855 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725818AbgCEBek (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 4 Mar 2020 20:34:40 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by orsmga103.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 04 Mar 2020 17:34:39 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,516,1574150400";
   d="scan'208";a="234301743"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga008.fm.intel.com with ESMTP; 04 Mar 2020 17:34:38 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Pu Wen <puwen@hygon.cn>
Subject: [PATCH v2 1/7] KVM: x86: Trace the original requested CPUID function
 in kvm_cpuid()
Date: Wed,  4 Mar 2020 17:34:31 -0800
Message-Id: <20200305013437.8578-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200305013437.8578-1-sean.j.christopherson@intel.com>
References: <20200305013437.8578-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Jan Kiszka <jan.kiszka@siemens.com>

Trace the requested CPUID function instead of the effective function,
e.g. if the requested function is out-of-range and KVM is emulating an
Intel CPU, as the intent of the tracepoint is to show if the output came
from the actual leaf as opposed to the max basic leaf via redirection.

Similarly, leave "found" as is, i.e. report that an entry was found if
and only if the requested entry was found.

Fixes: 43561123ab37 ("kvm: x86: Improve emulation of CPUID leaves 0BH and 1FH")
Signed-off-by: Jan Kiszka <jan.kiszka@siemens.com>
[Sean: Drop "found" semantic change, reword changelong accordingly ]
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/cpuid.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: x86: Fix warning due to implicit truncation on 32-bit KVM
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11420975
Return-Path: <SRS0=eotC=4W=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7BB5B14B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Mar 2020 00:24:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5C230214D8
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Mar 2020 00:24:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388567AbgCEAYZ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 4 Mar 2020 19:24:25 -0500
Received: from mga03.intel.com ([134.134.136.65]:26857 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2388407AbgCEAYZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 4 Mar 2020 19:24:25 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga103.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 04 Mar 2020 16:24:24 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,515,1574150400";
   d="scan'208";a="352228758"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga001.fm.intel.com with ESMTP; 04 Mar 2020 16:24:23 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: x86: Fix warning due to implicit truncation on 32-bit
 KVM
Date: Wed,  4 Mar 2020 16:24:22 -0800
Message-Id: <20200305002422.20968-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Explicitly cast the integer literal to an unsigned long when stuffing a
non-canonical value into the host virtual address during private memslot
deletion.  The explicit cast fixes a warning that gets promoted to an
error when running with KVM's newfangled -Werror setting.

  arch/x86/kvm/x86.c:9739:9: error: large integer implicitly truncated
  to unsigned type [-Werror=overflow]

Fixes: a3e967c0b87d3 ("KVM: Terminate memslot walks via used_slots"
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/x86.c | 8 ++++++--
 1 file changed, 6 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: x86: small optimization for is_mtrr_mask calculation
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11421113
Return-Path: <SRS0=eotC=4W=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 37480139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Mar 2020 02:46:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1DE0621556
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Mar 2020 02:46:08 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725861AbgCECqF (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 4 Mar 2020 21:46:05 -0500
Received: from szxga06-in.huawei.com ([45.249.212.32]:56004 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1725777AbgCECqE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 4 Mar 2020 21:46:04 -0500
Received: from DGGEMS412-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id A5866949316ACE906043;
        Thu,  5 Mar 2020 10:46:01 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS412-HUB.china.huawei.com
 (10.3.19.212) with Microsoft SMTP Server id 14.3.439.0; Thu, 5 Mar 2020
 10:45:54 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <jmattson@google.com>, <joro@8bytes.org>, <tglx@linutronix.de>,
        <mingo@redhat.com>, <bp@alien8.de>, <hpa@zytor.com>
CC: <linmiaohe@huawei.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <x86@kernel.org>
Subject: [PATCH] KVM: x86: small optimization for is_mtrr_mask calculation
Date: Thu, 5 Mar 2020 10:48:55 +0800
Message-ID: <1583376535-27255-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

We can get is_mtrr_mask by calculating (msr - 0x200) % 2 directly.

Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
---
 arch/x86/kvm/mtrr.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH 1/2] KVM: x86: VMX: rename 'kvm_area' to 'vmxon_region'
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11421481
Return-Path: <SRS0=eotC=4W=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B960592A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Mar 2020 10:01:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9A11221741
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Mar 2020 10:01:32 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="PsGdhXy0"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727185AbgCEKBb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Mar 2020 05:01:31 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:33403 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1725816AbgCEKBa (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Mar 2020 05:01:30 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1583402489;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=oswt/Kc8n1kZsUQ8QoQ1RiwQKyVHquWO2Ji98TMP3xg=;
        b=PsGdhXy0zwt+3ZjsuehX+gQ7rhoGYwAD/QviGvwePRZ1R4l0jXemQ6A0saP7RiORRIdbDI
        iANwdM9hxCWCUGZvE/RiAOleDF/3ApXXnM51KaZIIXtoavUfFtF/bkd0elf5xLs/pX9dNh
        Vz2MZTfVZtxypXpzwYyBxb5yj/ZQ4W0=
Received: from mail-wm1-f71.google.com (mail-wm1-f71.google.com
 [209.85.128.71]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-406-Sbip1xEpMwi7MrbWT18jsg-1; Thu, 05 Mar 2020 05:01:28 -0500
X-MC-Unique: Sbip1xEpMwi7MrbWT18jsg-1
Received: by mail-wm1-f71.google.com with SMTP id w12so1371979wmc.3
        for <kvm@vger.kernel.org>; Thu, 05 Mar 2020 02:01:27 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=oswt/Kc8n1kZsUQ8QoQ1RiwQKyVHquWO2Ji98TMP3xg=;
        b=D26/l+hkLdSYQl2QDWIPJCJxbz8u1df1n/tAD3SDtEU/gGr3L9pkHxVVjVDhjFf5IR
         GLovxkuLrptYCec6zvToHKHtDpq8xrEc7ttg1ONbLxcIbKNOK0rz/NClp8SOxbQqbF7t
         VkOpkfKS19FZtiEiQ2Ac8ta+Lyu+PATGj144YFtp4I06jfiWSZ95wllJzKeVV9DnSD5T
         Bpgwumk3LzK/DJ476Mkv5WBOlA8z8MvfCwRKyXIqRo24DDtN6nCXEkS/xMEH8mcH0qNr
         6o8gL+Rw1zaa1QLdABRSnWyySujk+lJ7oaUv8R9xx9QRTwMNEGCnH7sAlwuPb2VBACiD
         z/qA==
X-Gm-Message-State: ANhLgQ2AGDOkMjTzU3cJGUjqqXWtlU2NVCIqnlO8eiy0/66wUbezMr+P
        BRVVB19Fn23LOY5HQlha1+a7rCj35d3NH1+X7ckCnSasM9G7WkpnclTeCtN4Xm6UUJ7/lGeT3E4
        nhGYOyELx7NdC
X-Received: by 2002:a1c:ab07:: with SMTP id u7mr8242973wme.23.1583402486906;
        Thu, 05 Mar 2020 02:01:26 -0800 (PST)
X-Google-Smtp-Source: 
 ADFU+vuBnaABVorkSgwKmJdmaxfU2FtG7PnSy504t3kXi28pQPtb3RflQXkq36d2TuSjUNI9iAwShg==
X-Received: by 2002:a1c:ab07:: with SMTP id u7mr8242950wme.23.1583402486722;
        Thu, 05 Mar 2020 02:01:26 -0800 (PST)
Received: from vitty.brq.redhat.com (nat-pool-brq-t.redhat.com.
 [213.175.37.10])
        by smtp.gmail.com with ESMTPSA id
 f207sm10440025wme.9.2020.03.05.02.01.25
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 05 Mar 2020 02:01:25 -0800 (PST)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 1/2] KVM: x86: VMX: rename 'kvm_area' to 'vmxon_region'
Date: Thu,  5 Mar 2020 11:01:22 +0100
Message-Id: <20200305100123.1013667-2-vkuznets@redhat.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200305100123.1013667-1-vkuznets@redhat.com>
References: <20200305100123.1013667-1-vkuznets@redhat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The name 'kvm_area' is misleading (as we have way too many areas which are
KVM related), what alloc_kvm_area()/free_kvm_area() functions really do is
allocate/free VMXON region for all CPUs. Rename accordingly.

No functional change intended.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/vmx.c | 10 +++++-----
 1 file changed, 5 insertions(+), 5 deletions(-)

```
#### [PATCH v1 01/11] perf/x86/core: Support KVM to assign a dedicated counter for guest PEBS
##### From: Luwei Kang <luwei.kang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Luwei Kang <luwei.kang@intel.com>
X-Patchwork-Id: 11421453
Return-Path: <SRS0=eotC=4W=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6D91B139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Mar 2020 09:58:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 53E9121556
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Mar 2020 09:58:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727041AbgCEJ64 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Mar 2020 04:58:56 -0500
Received: from mga01.intel.com ([192.55.52.88]:50986 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725912AbgCEJ64 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Mar 2020 04:58:56 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga101.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 05 Mar 2020 01:58:55 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,517,1574150400";
   d="scan'208";a="234366402"
Received: from snr.bj.intel.com ([10.240.193.90])
  by orsmga008.jf.intel.com with ESMTP; 05 Mar 2020 01:58:49 -0800
From: Luwei Kang <luwei.kang@intel.com>
To: x86@kernel.org, linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: peterz@infradead.org, mingo@redhat.com, acme@kernel.org,
        mark.rutland@arm.com, alexander.shishkin@linux.intel.com,
        jolsa@redhat.com, namhyung@kernel.org, tglx@linutronix.de,
        bp@alien8.de, hpa@zytor.com, pbonzini@redhat.com,
        sean.j.christopherson@intel.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        pawan.kumar.gupta@linux.intel.com, ak@linux.intel.com,
        thomas.lendacky@amd.com, fenghua.yu@intel.com,
        kan.liang@linux.intel.com, like.xu@linux.intel.com
Subject: [PATCH v1 01/11] perf/x86/core: Support KVM to assign a dedicated
 counter for guest PEBS
Date: Fri,  6 Mar 2020 01:56:55 +0800
Message-Id: <1583431025-19802-2-git-send-email-luwei.kang@intel.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1583431025-19802-1-git-send-email-luwei.kang@intel.com>
References: <1583431025-19802-1-git-send-email-luwei.kang@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Kan Liang <kan.liang@linux.intel.com>

The PEBS event created by host needs to be assigned specific counters
requested by the guest, which means the guest and host counter indexes
have to be the same or fail to create. This is needed because PEBS leaks
counter indexes into the guest. Otherwise, the guest driver will be
confused by the counter indexes in the status field of the PEBS record.

A guest_dedicated_idx field is added to indicate the counter index
specifically requested by KVM. The dedicated event constraints would
constrain the counter in the host to the same numbered counter in guest.

A intel_ctrl_guest_dedicated_mask field is added to indicate the enabled
counters for guest PEBS events. The IA32_PEBS_ENABLE MSR will be switched
during the VMX transitions if intel_ctrl_guest_owned is set.

Originally-by: Andi Kleen <ak@linux.intel.com>
Signed-off-by: Kan Liang <kan.liang@linux.intel.com>
---
 arch/x86/events/intel/core.c | 60 +++++++++++++++++++++++++++++++++++++++++++-
 arch/x86/events/perf_event.h |  1 +
 include/linux/perf_event.h   |  2 ++
 kernel/events/core.c         |  1 +
 4 files changed, 63 insertions(+), 1 deletion(-)

```
#### [PATCH kvm-unit-tests 1/2] svm: rename and comment the pending_event_vmask test
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11421443
Return-Path: <SRS0=eotC=4W=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 87C3B17E0
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Mar 2020 09:36:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 676F72146E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Mar 2020 09:36:54 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="DKua6c6F"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726694AbgCEJgx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Mar 2020 04:36:53 -0500
Received: from mail-wr1-f66.google.com ([209.85.221.66]:42848 "EHLO
        mail-wr1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725937AbgCEJgx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Mar 2020 04:36:53 -0500
Received: by mail-wr1-f66.google.com with SMTP id v11so4148591wrm.9
        for <kvm@vger.kernel.org>; Thu, 05 Mar 2020 01:36:50 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=CXVlcp4rV/eWS8npZ8qAK0kaNe+d3hDfH3kziUz7KK0=;
        b=DKua6c6FJkL4IisF//4Yr39hw8aM46YyaBScqrA3m8S7eTXslBcOj4ZR6U/xaUtuOD
         j5VNLo1APEKvYzZtyuz/5OhCQlDg5S4uV1/jQQoHHNqD2E+ysH9AfUC8qaiqXAyt5Jpy
         Kq968RWGvn2weSg1ZbBsJbCCkQZnVN6shR7QfQrJ4ak6udUjAjG09p5ngbmxq5AVj9AU
         yGo0HBqQKyJRSg/2kzf5WQh/SqHmuoCeG0zf+QH4xxBjTObu4dJYj28LfbNS4QbFoqTI
         7TUgCwyCad6IxVLgurRBIwjsTwkcF4ySj0xO/lAhT4aGBup5g/U+pioos9Ye6wFaQDGF
         ucdw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :in-reply-to:references;
        bh=CXVlcp4rV/eWS8npZ8qAK0kaNe+d3hDfH3kziUz7KK0=;
        b=DXXHodvfN7NEdoCNCXZOWJ/u5mRGdtHCkMsxIcVb1in833wUFvpikqbSLH8OOLSQ8D
         Zh3jYL6v9AWzT6f3XG58QyuG5W5UzlrIqR8676OEttkpnQZk4UvLhShLnQxj7bwtPQzf
         H/ulKB3GONjBwPD5ykTYuCL9xECnI78V4lr7U4i703lB+WC0bV9raGc8mHPPnJLjfvAw
         6YMW5xRGuDhOHUXCV1COJn1y1AzHY1K0OfIedcNysUNyOkCWak5KDageG7xvl3YIxl6p
         9r7HYFFU2h5XMnGkgT00QUFrmIsZ7hIwiazSkL1KqKfzpuj6hmQRgBeeGWY+At4bZIZt
         ajfA==
X-Gm-Message-State: ANhLgQ1NYSKSQreqlQ0RDcm0HWygn5xTyac2GHF6t4i2qTFsp48TPtEP
        6L2c7m9FHjqDRU8xlcn4K2SjBRgA
X-Google-Smtp-Source: 
 ADFU+vvVrfkc5awtDes5Ju1KJawyQtZrz4WA8Vh5Khraa+TGd2MpC9AFGeB0khx9WiNDW0Kkly8/gw==
X-Received: by 2002:adf:f8cf:: with SMTP id f15mr1266856wrq.79.1583401009495;
        Thu, 05 Mar 2020 01:36:49 -0800 (PST)
Received: from 640k.localdomain.com ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 w1sm8188563wmc.11.2020.03.05.01.36.48
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 05 Mar 2020 01:36:49 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Cc: cavery@redhat.com
Subject: [PATCH kvm-unit-tests 1/2] svm: rename and comment the
 pending_event_vmask test
Date: Thu,  5 Mar 2020 10:36:45 +0100
Message-Id: <1583401006-57136-2-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1583401006-57136-1-git-send-email-pbonzini@redhat.com>
References: <1583401006-57136-1-git-send-email-pbonzini@redhat.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Both the pending_event and pending_event_vmask test are using the
V_INTR_MASKING field.  The difference is that pending_event_vmask
runs with host IF cleared, and therefore does not expect INTR
vmexits.  Rename the test to clarify this, and add comments to
explain what's going on.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 x86/svm.c | 25 ++++++++++++++++---------
 1 file changed, 16 insertions(+), 9 deletions(-)

```
#### [PATCH v2] KVM: fix Kconfig menu text for -Werror
##### From: "Jason A. Donenfeld" <Jason@zx2c4.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Jason A. Donenfeld" <Jason@zx2c4.com>
X-Patchwork-Id: 11421219
Return-Path: <SRS0=eotC=4W=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1370214BC
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Mar 2020 06:06:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E288021556
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Mar 2020 06:06:25 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=zx2c4.com header.i=@zx2c4.com
 header.b="hqjjb1oP"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725944AbgCEGGW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Mar 2020 01:06:22 -0500
Received: from frisell.zx2c4.com ([192.95.5.64]:60245 "EHLO frisell.zx2c4.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725838AbgCEGGW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Mar 2020 01:06:22 -0500
Received: by frisell.zx2c4.com (ZX2C4 Mail Server) with ESMTP id 08a2443c;
        Thu, 5 Mar 2020 06:01:42 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha1; c=relaxed; d=zx2c4.com; h=from:to:cc
        :subject:date:message-id:in-reply-to:references:mime-version
        :content-transfer-encoding; s=mail; bh=qf7iBnoAP1jFyvRyxTLvRHeDZ
        Gw=; b=hqjjb1oPQyzgtuRHxsmeTnPMhLgFEGmjPwrYAhrnEz+awDd8V/6AG0VQE
        WSf3c5f5/Hq2YKx0cNHxhawSVObj9ZfX3ddsaMbq3qQP1ycGVZ+QtnVmRxNUWgqm
        I6MY0pvNK+oU9qCybL7j7U3FmpgOYhDsOl+oQR3NCsw+R5JxerzupqC0Ru+XOAOW
        78BmlQkh9mPkIHnO7WRddf+X2we6OGpN1e3gck80CAgXYny4dFzBgAP5GZ+HyjNK
        QcTrIi+IsUD6rT8ik6Jsjyvm4lE52toOye2GjaHLGLr83qUzZWxV9XnCdEraxCTQ
        umpWOehP+LLOvv9GKiIwRvBuJR5qA==
Received: by frisell.zx2c4.com (ZX2C4 Mail Server) with ESMTPSA id f156eac8
 (TLSv1.2:ECDHE-RSA-AES256-GCM-SHA384:256:NO);
        Thu, 5 Mar 2020 06:01:41 +0000 (UTC)
From: "Jason A. Donenfeld" <Jason@zx2c4.com>
To: pbonzini@redhat.com, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, sean.j.christopherson@intel.com
Cc: "Jason A. Donenfeld" <Jason@zx2c4.com>
Subject: [PATCH v2] KVM: fix Kconfig menu text for -Werror
Date: Thu,  5 Mar 2020 14:06:04 +0800
Message-Id: <20200305060604.8076-1-Jason@zx2c4.com>
In-Reply-To: <20200304190750.GF21662@linux.intel.com>
References: <20200304190750.GF21662@linux.intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This was evidently copy and pasted from the i915 driver, but the text
wasn't updated.

Fixes: 4f337faf1c55 ("KVM: allow disabling -Werror")
Signed-off-by: Jason A. Donenfeld <Jason@zx2c4.com>
---
 arch/x86/kvm/Kconfig | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2 1/4] x86/kvm/hyper-v: Align the hcall param for kvm_hyperv_exit
##### From: Jon Doron <arilou@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jon Doron <arilou@gmail.com>
X-Patchwork-Id: 11421893
Return-Path: <SRS0=eotC=4W=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 90FFF138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Mar 2020 14:01:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 679962146E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Mar 2020 14:01:45 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="oceuHmUM"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726811AbgCEOBo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Mar 2020 09:01:44 -0500
Received: from mail-wm1-f67.google.com ([209.85.128.67]:50692 "EHLO
        mail-wm1-f67.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726173AbgCEOBo (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Mar 2020 09:01:44 -0500
Received: by mail-wm1-f67.google.com with SMTP id a5so6448165wmb.0;
        Thu, 05 Mar 2020 06:01:42 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=g1gCW4wuMkAhJVczZU/0rxkNbCY/76UCAy/6zzDIpdQ=;
        b=oceuHmUMgk/rn3OAkyGgGVHh9NLeWrzgCnudqNZYR/kuLZ69dBuMtFkjeoPvlUC+S5
         oKrHbcvWqi5RgvJwhk5KAAbCcNgxQMHXowfPYVSxBwgGPIXbxylgZz1AytLXlCLw2ULa
         a8vPb6zGKQkH+exw8Yrs5rgGfdQuMSaJ7yE/HqELIH68qmP81uXv1yNmFECTpB12WuEY
         QIi7XSHhGfqfxPm2cyVs+NYANSf+z8ZoXPLffD0GpEFvCTxQJOgS6xvY7oLrzB/YPVC4
         K/YaI1qNREm8TxSMmrd9Tg1EtPCBbAPQuI9Ynoc0bf+PSlXjfHi6Gw2PoAnsLYxKIwZ+
         umIA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=g1gCW4wuMkAhJVczZU/0rxkNbCY/76UCAy/6zzDIpdQ=;
        b=sKRIO8WLjOPp/+N8VXVZ4x2XJ76nenNZOarQTB1+LF1Wzf/3P/Mgd6TEJEBkwjHeEs
         ygcKLJx8FKs/aDm0CFUmA7iDsOkzgXlb90OWUjyxf5JiWFHF9Ad1Vn+xoCex4UgWBgWS
         P/O6YK4vGnP6ow9Uy+aRXRcz0E+st+BH3Ag5J0Gl1NXb4XQHDzRxuQJI0Yw0p0r7+8lJ
         oZudgLVoEYwOXZ6T74xWgXq0gPzqOMvBgOnMTYw0syNn635UR93LYjfCciBUz2UrXjlG
         wP+e1vpU/29atf5xk7glqFhJhMWZofUWfIhZrGzGHMMAMV4anVMImmTjU/SkyNa6WnWD
         4ilw==
X-Gm-Message-State: ANhLgQ28usegjv75rHwR1ElDD631JQaX5Uj7gVSNzgN4YN33CtRQ6Ept
        NISDEerpyyjEniOJF7oJYp8rZcpU
X-Google-Smtp-Source: 
 ADFU+vueCuoNuCRsOedGO1DKRNivBHPo2mT33aerbdX/BUEyPycLeTyHsse+Ct7KKHcDxcrvVDNSDQ==
X-Received: by 2002:a1c:25c5:: with SMTP id
 l188mr10314844wml.105.1583416899650;
        Thu, 05 Mar 2020 06:01:39 -0800 (PST)
Received: from linux.local ([31.154.166.148])
        by smtp.gmail.com with ESMTPSA id
 c72sm3379824wme.35.2020.03.05.06.01.38
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 05 Mar 2020 06:01:39 -0800 (PST)
From: Jon Doron <arilou@gmail.com>
To: kvm@vger.kernel.org, linux-hyperv@vger.kernel.org
Cc: vkuznets@redhat.com, Jon Doron <arilou@gmail.com>
Subject: [PATCH v2 1/4] x86/kvm/hyper-v: Align the hcall param for
 kvm_hyperv_exit
Date: Thu,  5 Mar 2020 16:01:39 +0200
Message-Id: <20200305140142.413220-2-arilou@gmail.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200305140142.413220-1-arilou@gmail.com>
References: <20200305140142.413220-1-arilou@gmail.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Jon Doron <arilou@gmail.com>
---
 include/uapi/linux/kvm.h | 1 +
 1 file changed, 1 insertion(+)

```
