

#### [PATCH v2 00/16] KVM: Add Xen hypercall and shared info pages
##### From: David Woodhouse <dwmw2@infradead.org>

```c
From patchwork Sun Dec  6 11:03:11 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: David Woodhouse <dwmw2@infradead.org>
X-Patchwork-Id: 11953987
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 589E8C19425
	for <kvm@archiver.kernel.org>; Sun,  6 Dec 2020 11:05:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 33F2A22E03
	for <kvm@archiver.kernel.org>; Sun,  6 Dec 2020 11:05:19 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727476AbgLFLFE (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 6 Dec 2020 06:05:04 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:41910 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727195AbgLFLE4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 6 Dec 2020 06:04:56 -0500
Received: from casper.infradead.org (casper.infradead.org
 [IPv6:2001:8b0:10b:1236::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id BC542C08E863
        for <kvm@vger.kernel.org>; Sun,  6 Dec 2020 03:03:59 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=casper.20170209;
 h=Sender:Content-Transfer-Encoding:
        Content-Type:MIME-Version:Message-Id:Date:Subject:Cc:To:From:Reply-To:
        Content-ID:Content-Description:In-Reply-To:References;
        bh=boRAwl+8YI6+G24ygg7y9yhULYmaOwaszHt5VWh3u9Q=;
 b=lrsLhNrr0jzWTw3Du4KdVtnOud
        3HuSyL9ZTVy/bYSUsuhUSxnKBTsltOM61DyVaNlmoogmNcUxJDZII3RVzNXAO1/9K8XgMMuzf/P4l
        6emUyNquJdd8CR29hWyrkGycNgSPyOXSQDIvRbfPMETtT2BEN/b6fFT3MFzadES8JzuDvxfwXDKzq
        sT1Z288tlUsKUgM4CPbazo9CAfp4eMY5LeWRhXQolmA40lcfoi/5nD7X7XqVJ7LYKS6E7y+zJn6iF
        hQGdwU9OspUanzW02imyhfVdzc1Qs1b2/6lrVjTFIYnKJBPg+vqVtecXX6qui5h1EAQoZje3pLWMb
        0cCuVsbQ==;
Received: from i7.infradead.org ([2001:8b0:10b:1:21e:67ff:fecb:7a92])
        by casper.infradead.org with esmtpsa (Exim 4.92.3 #3 (Red Hat Linux))
        id 1klrpD-0006Fn-WE; Sun, 06 Dec 2020 11:03:41 +0000
Received: from dwoodhou by i7.infradead.org with local (Exim 4.94 #2 (Red Hat
 Linux))
        id 1klrpD-000jp8-Ia; Sun, 06 Dec 2020 11:03:31 +0000
From: David Woodhouse <dwmw2@infradead.org>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Ankur Arora <ankur.a.arora@oracle.com>,
        Joao Martins <joao.m.martins@oracle.com>,
        Boris Ostrovsky <boris.ostrovsky@oracle.com>,
        Sean Christopherson <seanjc@google.com>, graf@amazon.com,
        iaslan@amazon.de
Subject: [PATCH v2 00/16] KVM: Add Xen hypercall and shared info pages
Date: Sun,  6 Dec 2020 11:03:11 +0000
Message-Id: <20201206110327.175629-1-dwmw2@infradead.org>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Sender: David Woodhouse <dwmw2@infradead.org>
X-SRS-Rewrite: SMTP reverse-path rewritten from <dwmw2@infradead.org> by
 casper.infradead.org. See http://www.infradead.org/rpr.html
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Reviving the first section (so far) of a patch set that Joao posted as 
RFC last year:

https://lore.kernel.org/kvm/20190220201609.28290-1-joao.m.martins@oracle.com/

This adds basic hypercall interception support, and adds support for
timekeeping and runstate-related shared info regions.

I've updated and reworked the original a bit, including (in my v1):
 • Support for 32-bit guests
 • 64-bit second support in wallclock
 • Time counters for runnable/blocked states in runstate support
 • Self-tests
 • Fixed Viridian coexistence
 • No new KVM_CAP_XEN_xxx, just more bits returned by KVM_CAP_XEN_HVM

v2: 
 • Remember the RCU read-critical sections on using the shared info pages
 • Fix 32-bit build of compat structures (which we use there too)
 • Use RUNSTATE_blocked as initial state not RUNSTATE_runnable
 • Include documentation, add cosmetic KVM_XEN_HVM_CONFIG_HYPERCALL_MSR

David Woodhouse (7):
      KVM: Fix arguments to kvm_{un,}map_gfn()
      KVM: x86/xen: Fix coexistence of Xen and Hyper-V hypercalls
      KVM: x86/xen: latch long_mode when hypercall page is set up
      KVM: x86/xen: add definitions of compat_shared_info, compat_vcpu_info
      xen: add wc_sec_hi to struct shared_info
      KVM: x86: declare Xen HVM shared info capability and add test case
      KVM: Add documentation for Xen hypercall and shared_info updates

Joao Martins (9):
      KVM: x86/xen: fix Xen hypercall page msr handling
      KVM: x86/xen: intercept xen hypercalls if enabled
      KVM: x86/xen: add KVM_XEN_HVM_SET_ATTR/KVM_XEN_HVM_GET_ATTR
      KVM: x86/xen: register shared_info page
      KVM: x86/xen: setup pvclock updates
      KVM: x86/xen: update wallclock region
      KVM: x86/xen: register vcpu info
      KVM: x86/xen: register vcpu time info region
      KVM: x86/xen: register runstate info

 Documentation/virt/kvm/api.rst                       | 119 ++++++++++++++++++++++++++++++++++
 arch/x86/include/asm/kvm_host.h                      |  23 +++++++
 arch/x86/include/asm/xen/interface.h                 |   3 +
 arch/x86/kvm/Makefile                                |   2 +-
 arch/x86/kvm/hyperv.c                                |  40 ++++++++----
 arch/x86/kvm/trace.h                                 |  36 +++++++++++
 arch/x86/kvm/x86.c                                   | 110 ++++++++++++++++++++------------
 arch/x86/kvm/x86.h                                   |   1 +
 arch/x86/kvm/xen.c                                   | 557 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 arch/x86/kvm/xen.h                                   |  83 ++++++++++++++++++++++++
 include/linux/kvm_host.h                             |  34 +++++-----
 include/uapi/linux/kvm.h                             |  48 ++++++++++++++
 include/xen/interface/xen.h                          |   4 +-
 tools/testing/selftests/kvm/Makefile                 |   2 +
 tools/testing/selftests/kvm/lib/kvm_util.c           |   1 +
 tools/testing/selftests/kvm/x86_64/xen_shinfo_test.c | 187 ++++++++++++++++++++++++++++++++++++++++++++++++++++++
 tools/testing/selftests/kvm/x86_64/xen_vmcall_test.c | 150 +++++++++++++++++++++++++++++++++++++++++++
 virt/kvm/kvm_main.c                                  |   8 +--
 18 files changed, 1335 insertions(+), 73 deletions(-)
```
#### [PATCH 0/8] gitlab-ci: Add accelerator-specific Linux jobs
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
From patchwork Sun Dec  6 18:55:00 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 11954273
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,
	TVD_PH_BODY_ACCOUNTS_PRE,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B5015C433FE
	for <kvm@archiver.kernel.org>; Sun,  6 Dec 2020 18:57:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 791D622E03
	for <kvm@archiver.kernel.org>; Sun,  6 Dec 2020 18:57:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727432AbgLFS4n (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 6 Dec 2020 13:56:43 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:43618 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726440AbgLFS4n (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sun, 6 Dec 2020 13:56:43 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1607280916;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=5L9zYVEk7UDV9e8J6jUWmDLNneFBSRjTDjE9eeZGMJ4=;
        b=AlmlVAjbudmTkFWzmCLl/1/kkJ9ebmqJdDSKT5+hc63KjH+NgghvApaRkA78PP9TfId15E
        RxOl30jqb9pFeDoJqLIyhtiVKLUWlGoDQQ5PxJxRUy52TdcYB+tHYL3Bo2n3k1O80lzkOC
        PVmWlvI8vdZF7adadAz8bFiXVou1rwQ=
Received: from mail-wm1-f71.google.com (mail-wm1-f71.google.com
 [209.85.128.71]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-578-IMhiZGzCPiGkIpXD7dKlCw-1; Sun, 06 Dec 2020 13:55:13 -0500
X-MC-Unique: IMhiZGzCPiGkIpXD7dKlCw-1
Received: by mail-wm1-f71.google.com with SMTP id v5so4349064wmj.0
        for <kvm@vger.kernel.org>; Sun, 06 Dec 2020 10:55:13 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=5L9zYVEk7UDV9e8J6jUWmDLNneFBSRjTDjE9eeZGMJ4=;
        b=B/J2t7CPigC7tfeO2P3YQ688x0I01SFVXeFiIhLnQSxk/gTyvnVTyEQSkvDV6vuyRd
         6YNvgFt9S/9KdOzTLCFmWFgsGumM19N1NSRlfQUllOmY0flSdbMp09I79hP3rU3oD6sS
         YZL+w3T0/K8tZa4Djvlp/UEa8qOkIP0kEH1yBSmKkXoN3nB7pz7doTMIKNEDxrB5MkPZ
         QtaT4zQ9YdrDHNYX9+hbipSXPTb/5XaloP5UVEc4BUtWXLr6JAQs6RpqtpqyKsFgj8yE
         4ve4umPqoHphE6Ie5JaJWu/r33uG+8vcI/L+pmCvr7IlyubYNzgxfwpjXRiLHjTzsqW9
         zjHg==
X-Gm-Message-State: AOAM532jLDWc9gQLN13VmItDputHN6Uyf/CLqZqlIkDKoCMdOm2WJD6/
        SaylyMHBr+iATtNuNn0kDJOVLZMK80xMdSLJgJxwdYtjJ1jmVga6QndmnUUHlD47kIvxiXz2904
        ALxry/tX31p4d
X-Received: by 2002:a1c:6056:: with SMTP id u83mr14528860wmb.90.1607280911972;
        Sun, 06 Dec 2020 10:55:11 -0800 (PST)
X-Google-Smtp-Source: 
 ABdhPJyCSZGi5rbiGoVRoGKRNGTcTbBvyODVVSoiL6GLaxlOiqbwRFYQlZdlM1E+jjVm6ac4G5YFvw==
X-Received: by 2002:a1c:6056:: with SMTP id u83mr14528834wmb.90.1607280911735;
        Sun, 06 Dec 2020 10:55:11 -0800 (PST)
Received: from localhost.localdomain (101.red-88-21-206.staticip.rima-tde.net.
 [88.21.206.101])
        by smtp.gmail.com with ESMTPSA id
 a62sm4051738wmh.40.2020.12.06.10.55.09
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Sun, 06 Dec 2020 10:55:10 -0800 (PST)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
To: qemu-devel@nongnu.org
Cc: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>, =?utf-8?q?A?=
	=?utf-8?q?lex_Benn=C3=A9e?= <alex.bennee@linaro.org>,
 Aleksandar Rikalo <aleksandar.rikalo@syrmia.com>,
 xen-devel@lists.xenproject.org, kvm@vger.kernel.org,
 Wainer dos Santos Moschetta <wainersm@redhat.com>,
 Jiaxun Yang <jiaxun.yang@flygoat.com>,
 Willian Rampazzo <wrampazz@redhat.com>, Paul Durrant <paul@xen.org>,
 Huacai Chen <chenhc@lemote.com>, Anthony Perard <anthony.perard@citrix.com>,
 Marcelo Tosatti <mtosatti@redhat.com>,
 Stefano Stabellini <sstabellini@kernel.org>,
 Claudio Fontana <cfontana@suse.de>, Halil Pasic <pasic@linux.ibm.com>,
 Peter Maydell <peter.maydell@linaro.org>,
 Christian Borntraeger <borntraeger@de.ibm.com>,
 Cornelia Huck <cohuck@redhat.com>,
 David Gibson <david@gibson.dropbear.id.au>, Thomas Huth <thuth@redhat.com>,
 Paolo Bonzini <pbonzini@redhat.com>, qemu-s390x@nongnu.org,
 Aurelien Jarno <aurelien@aurel32.net>, qemu-arm@nongnu.org
Subject: [PATCH 0/8] gitlab-ci: Add accelerator-specific Linux jobs
Date: Sun,  6 Dec 2020 19:55:00 +0100
Message-Id: <20201206185508.3545711-1-philmd@redhat.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

I was custom to use Travis-CI for testing KVM builds on s390x/ppc
with the Travis-CI jobs.

During October Travis-CI became unusable for me (extremely slow,
see [1]). Then my free Travis account got updated to the new
"10K credit minutes allotment" [2] which I burned without reading
the notification email in time (I'd burn them eventually anyway).

Today Travis-CI is pointless to me. While I could pay to run my
QEMU jobs, I don't think it is fair for an Open Source project to
ask its forks to pay for a service.

As we want forks to run some CI before contributing patches, and
we have cross-build Docker images available for Linux hosts, I
added some cross KVM/Xen build jobs to Gitlab-CI.

Cross-building doesn't have the same coverage as native building,
as we can not run the tests. But this is still useful to get link
failures.

Each job is added in its own YAML file, so it is easier to notify
subsystem maintainers in case of troubles.

Resulting pipeline:
https://gitlab.com/philmd/qemu/-/pipelines/225948077

Regards,

Phil.

[1] https://travis-ci.community/t/build-delays-for-open-source-project/10272
[2] https://blog.travis-ci.com/2020-11-02-travis-ci-new-billing

Philippe Mathieu-Daudé (8):
  gitlab-ci: Replace YAML anchors by extends (cross_system_build_job)
  gitlab-ci: Introduce 'cross_accel_build_job' template
  gitlab-ci: Add KVM X86 cross-build jobs
  gitlab-ci: Add KVM ARM cross-build jobs
  gitlab-ci: Add KVM s390x cross-build jobs
  gitlab-ci: Add KVM PPC cross-build jobs
  gitlab-ci: Add KVM MIPS cross-build jobs
  gitlab-ci: Add Xen cross-build jobs

 .gitlab-ci.d/crossbuilds-kvm-arm.yml   |  5 +++
 .gitlab-ci.d/crossbuilds-kvm-mips.yml  |  5 +++
 .gitlab-ci.d/crossbuilds-kvm-ppc.yml   |  5 +++
 .gitlab-ci.d/crossbuilds-kvm-s390x.yml |  6 +++
 .gitlab-ci.d/crossbuilds-kvm-x86.yml   |  6 +++
 .gitlab-ci.d/crossbuilds-xen.yml       | 14 +++++++
 .gitlab-ci.d/crossbuilds.yml           | 52 ++++++++++++++++----------
 .gitlab-ci.yml                         |  6 +++
 MAINTAINERS                            |  6 +++
 9 files changed, 85 insertions(+), 20 deletions(-)
 create mode 100644 .gitlab-ci.d/crossbuilds-kvm-arm.yml
 create mode 100644 .gitlab-ci.d/crossbuilds-kvm-mips.yml
 create mode 100644 .gitlab-ci.d/crossbuilds-kvm-ppc.yml
 create mode 100644 .gitlab-ci.d/crossbuilds-kvm-s390x.yml
 create mode 100644 .gitlab-ci.d/crossbuilds-kvm-x86.yml
 create mode 100644 .gitlab-ci.d/crossbuilds-xen.yml
```
