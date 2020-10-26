

#### [PATCH 0/2] Fix null pointer dereference in kvm_msr_ignored_check
##### From: Peter Xu <peterx@redhat.com>

```c
From patchwork Sun Oct 25 18:53:32 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11855387
Return-Path: <SRS0=Ww7j=EA=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-6.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=no
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id AE305C388F7
	for <kvm@archiver.kernel.org>; Sun, 25 Oct 2020 18:53:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 625E322260
	for <kvm@archiver.kernel.org>; Sun, 25 Oct 2020 18:53:42 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="aiX+9t2+"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1418308AbgJYSxl (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 25 Oct 2020 14:53:41 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:20302 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1417005AbgJYSxl (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sun, 25 Oct 2020 14:53:41 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1603652019;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=l9opdhjO8wDOyQJdye7Bnt0YjHd2izk2OycmVO/q0mQ=;
        b=aiX+9t2+xZ1n8/qalb0NvsGI7a8Quv7R7WJsUDEpp0K3xEK2MkVPSqkt17HfrnGTwyqcSm
        4uOrmV+iMVfqk4/bLOs9AgPUaDkWB5+PmyeYqPNUL0zCSh13jMJKXTsXSdAFG9SRSnUFwY
        HxjNOSuFy7Jr6qIvGNPInQ5dYjUGoGM=
Received: from mail-qt1-f198.google.com (mail-qt1-f198.google.com
 [209.85.160.198]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-596-kn39ADr1MUurC6PvNMNQtw-1; Sun, 25 Oct 2020 14:53:37 -0400
X-MC-Unique: kn39ADr1MUurC6PvNMNQtw-1
Received: by mail-qt1-f198.google.com with SMTP id c4so4909362qtx.20
        for <kvm@vger.kernel.org>; Sun, 25 Oct 2020 11:53:37 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=l9opdhjO8wDOyQJdye7Bnt0YjHd2izk2OycmVO/q0mQ=;
        b=OyEkHWhRwKchb56a205tgNrU0I8faWpkGCoiRHeQLj+OduJ54slyNOkDp7X7/R6TS5
         OgHKsFhfoWK8FEFET82qnYF2VtsbqlOabCAW6SR/HCE4WADl2WXxymHV0hfMHPQbFctU
         uP2x1HJlD0JvLSBSxBUZKCb7lo914MVLabnskAz4pduzdsveqKYyr/xWtVlh5xrkaKTO
         kcb3Hrw1LtEVDvt0due22a3unSo4VdmZgjq4xRiHOr1CQaqgKwZ9zSkyWXL5B2LwNJJ8
         KmyKsC27uN0qtrkptakk6LI0DqyXcFm2nloUKo8BtIkjs3TbCuA0R0pA/8s5Qlk17NvV
         We8w==
X-Gm-Message-State: AOAM533ztTtrwwxKY+fCP9aOToC6sNYysF/TGrgp/rNjBhLeFhW+pp5+
        QB2q1umcAVO3y2sUGEW54ZGGrkwEcglkrd2FSyXQiR20dOHnVTTKf2kMfbf9lfWSOhDWRK2yQAg
        eZdrFFStelQrJ
X-Received: by 2002:ac8:3510:: with SMTP id
 y16mr13427400qtb.300.1603652017282;
        Sun, 25 Oct 2020 11:53:37 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJx5KhSGchYzMGbuUSH7VwFwskXs0eZ8seChI+2sD6xWskBYWXULVezbnh/8TWgCLDUqJS/SKA==
X-Received: by 2002:ac8:3510:: with SMTP id
 y16mr13427384qtb.300.1603652017070;
        Sun, 25 Oct 2020 11:53:37 -0700 (PDT)
Received: from xz-x1.redhat.com
 (toroon474qw-lp140-04-174-95-215-133.dsl.bell.ca. [174.95.215.133])
        by smtp.gmail.com with ESMTPSA id y3sm5305224qto.2.2020.10.25.11.53.35
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Sun, 25 Oct 2020 11:53:36 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>, peterx@redhat.com,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Subject: [PATCH 0/2] Fix null pointer dereference in kvm_msr_ignored_check
Date: Sun, 25 Oct 2020 14:53:32 -0400
Message-Id: <20201025185334.389061-1-peterx@redhat.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Bug report: https://lore.kernel.org/kvm/bug-209845-28872@https.bugzilla.kernel.org%2F/

Unit test attached, which can reproduce the same issue.

Thanks,

Peter Xu (2):
  KVM: selftests: Add get featured msrs test case
  KVM: X86: Fix null pointer reference for KVM_GET_MSRS

 arch/x86/kvm/x86.c                            |  4 +-
 .../testing/selftests/kvm/include/kvm_util.h  |  3 +
 tools/testing/selftests/kvm/lib/kvm_util.c    | 14 +++++
 .../testing/selftests/kvm/x86_64/state_test.c | 58 +++++++++++++++++++
 4 files changed, 77 insertions(+), 2 deletions(-)
```
