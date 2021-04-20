

#### [PATCH V4 0/3] vDPA/ifcvf: enables Intel C5000X-PL virtio-blk
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
From patchwork Mon Apr 19 06:33:23 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 12210883
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 62545C433ED
	for <kvm@archiver.kernel.org>; Mon, 19 Apr 2021 06:38:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3E49761104
	for <kvm@archiver.kernel.org>; Mon, 19 Apr 2021 06:38:55 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231433AbhDSGjW (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 19 Apr 2021 02:39:22 -0400
Received: from mga12.intel.com ([192.55.52.136]:32762 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229630AbhDSGjW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 19 Apr 2021 02:39:22 -0400
IronPort-SDR: 
 fithrntEnbkqI+ZMRifUZKEJ4w1Rd+MaNQK3XHISLrAcHOK0wAMP3hacVium1EG8E89W12tc9K
 E15C8K1eYT2g==
X-IronPort-AV: E=McAfee;i="6200,9189,9958"; a="174766091"
X-IronPort-AV: E=Sophos;i="5.82,233,1613462400";
   d="scan'208";a="174766091"
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 18 Apr 2021 23:38:52 -0700
IronPort-SDR: 
 WSKcKiyUlWqe20hedjo0o9RhDUU6UeZ9trksqtiStHNusdT3iocgr7fAx25JiX0s6ycTxP+qyu
 MLxSXq9iDVOg==
X-IronPort-AV: E=Sophos;i="5.82,233,1613462400";
   d="scan'208";a="523328521"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.193.73])
  by fmsmga001-auth.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 18 Apr 2021 23:38:50 -0700
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: jasowang@redhat.com, mst@redhat.com, lulu@redhat.com,
        sgarzare@redhat.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH V4 0/3] vDPA/ifcvf: enables Intel C5000X-PL virtio-blk
Date: Mon, 19 Apr 2021 14:33:23 +0800
Message-Id: <20210419063326.3748-1-lingshan.zhu@intel.com>
X-Mailer: git-send-email 2.27.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series enabled Intel FGPA SmartNIC C5000X-PL virtio-blk for vDPA.

This series requires:
Stefano's vdpa block patchset: https://lkml.org/lkml/2021/3/15/2113
my patchset to enable Intel FGPA SmartNIC C5000X-PL virtio-net for vDPA:
https://lkml.org/lkml/2021/3/17/432

changes from V3:
remove (pdev->device < 0x1000 || pdev->device > 0x107f) checks in
probe(), because id_table already cut them off(Jason)

changes from V2:
both get_features() and get_config_size() use switch code block
now(Stefano)

changes from V1:
(1)add comments to explain this driver drives virtio modern devices
and transitional devices in modern mode.(Jason)
(2)remove IFCVF_BLK_SUPPORTED_FEATURES, use hardware feature bits
directly(Jason)
(3)add error handling and message in get_config_size(Stefano)

Thanks!

Zhu Lingshan (3):
  vDPA/ifcvf: deduce VIRTIO device ID when probe
  vDPA/ifcvf: enable Intel C5000X-PL virtio-block for vDPA
  vDPA/ifcvf: get_config_size should return dev specific config size

 drivers/vdpa/ifcvf/ifcvf_base.h |  9 ++++-
 drivers/vdpa/ifcvf/ifcvf_main.c | 65 ++++++++++++++++++++++++++-------
 2 files changed, 59 insertions(+), 15 deletions(-)
```
#### [PATCH 00/30] KVM: x86: hyper-v: Fine-grained access check to Hyper-V
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Mon Apr 19 16:00:57 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 12212205
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-10.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8CD46C433B4
	for <kvm@archiver.kernel.org>; Mon, 19 Apr 2021 16:01:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 664CD61363
	for <kvm@archiver.kernel.org>; Mon, 19 Apr 2021 16:01:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S241918AbhDSQCL (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 19 Apr 2021 12:02:11 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:57590 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S238882AbhDSQCH (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 19 Apr 2021 12:02:07 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1618848097;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=7buKlKcIzwYjYtSsOH62T0G/8Lr2YM3SFG1mxWF3n4I=;
        b=Cax9/WrbAySxtOAOEwtohVSQ/puBI/uuY6mIwjmtk58dGAkbmybMmewk3CSE+mKAzirpRD
        wPXjt20Y+kHoTc49W7rMbcCe7YTcPNDoUja3fu0ihppdC++wAMUxvnEbss5FC9HXG0h0lj
        TkoU04rQ3CikQABoVA6BUSA/woJIji4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-509-em6KCmNiM9qdl3VAMQbOww-1; Mon, 19 Apr 2021 12:01:33 -0400
X-MC-Unique: em6KCmNiM9qdl3VAMQbOww-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 775168030D5;
        Mon, 19 Apr 2021 16:01:31 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.193.113])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E33CE2BFEC;
        Mon, 19 Apr 2021 16:01:28 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Siddharth Chandrasekaran <sidcha@amazon.de>,
        linux-kernel@vger.kernel.org
Subject: [PATCH 00/30] KVM: x86: hyper-v: Fine-grained access check to Hyper-V
 hypercalls and MSRs
Date: Mon, 19 Apr 2021 18:00:57 +0200
Message-Id: <20210419160127.192712-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Changes since RFC:
- KVM_CAP_HYPERV_ENFORCE_CPUID introduced. Turns out that at least QEMU
  is not doing a great job setting Hyper-V CPUID entries for various
  configurations (when not all enlightenments are enabled).
- Added a selftest.
- Add Wei's A-b tag to PATCH1.

Currently, all implemented Hyper-V features (MSRs and hypercalls) are
available unconditionally to all Hyper-V enabled guests. This is not
ideal as KVM userspace may decide to provide only a subset of the
currently implemented features to emulate an older Hyper-V version,
to reduce attack surface,... Implement checks against guest visible
CPUIDs for all currently implemented MSRs and hypercalls.

Vitaly Kuznetsov (30):
  asm-generic/hyperv: add HV_STATUS_ACCESS_DENIED definition
  KVM: x86: hyper-v: Introduce KVM_CAP_HYPERV_ENFORCE_CPUID
  KVM: x86: hyper-v: Cache guest CPUID leaves determining features
    availability
  KVM: x86: hyper-v: Prepare to check access to Hyper-V MSRs
  KVM: x86: hyper-v: Honor HV_MSR_HYPERCALL_AVAILABLE privilege bit
  KVM: x86: hyper-v: Honor HV_MSR_VP_RUNTIME_AVAILABLE privilege bit
  KVM: x86: hyper-v: Honor HV_MSR_TIME_REF_COUNT_AVAILABLE privilege bit
  KVM: x86: hyper-v: Honor HV_MSR_VP_INDEX_AVAILABLE privilege bit
  KVM: x86: hyper-v: Honor HV_MSR_RESET_AVAILABLE privilege bit
  KVM: x86: hyper-v: Honor HV_MSR_REFERENCE_TSC_AVAILABLE privilege bit
  KVM: x86: hyper-v: Honor HV_MSR_SYNIC_AVAILABLE privilege bit
  KVM: x86: hyper-v: Honor HV_MSR_SYNTIMER_AVAILABLE privilege bit
  KVM: x86: hyper-v: Honor HV_MSR_APIC_ACCESS_AVAILABLE privilege bit
  KVM: x86: hyper-v: Honor HV_ACCESS_FREQUENCY_MSRS privilege bit
  KVM: x86: hyper-v: Honor HV_ACCESS_REENLIGHTENMENT privilege bit
  KVM: x86: hyper-v: Honor HV_FEATURE_GUEST_CRASH_MSR_AVAILABLE
    privilege bit
  KVM: x86: hyper-v: Honor HV_FEATURE_DEBUG_MSRS_AVAILABLE privilege bit
  KVM: x86: hyper-v: Inverse the default in hv_check_msr_access()
  KVM: x86: hyper-v: Honor HV_STIMER_DIRECT_MODE_AVAILABLE privilege bit
  KVM: x86: hyper-v: Prepare to check access to Hyper-V hypercalls
  KVM: x86: hyper-v: Check access to HVCALL_NOTIFY_LONG_SPIN_WAIT
    hypercall
  KVM: x86: hyper-v: Honor HV_POST_MESSAGES privilege bit
  KVM: x86: hyper-v: Honor HV_SIGNAL_EVENTS privilege bit
  KVM: x86: hyper-v: Honor HV_DEBUGGING privilege bit
  KVM: x86: hyper-v: Honor HV_X64_REMOTE_TLB_FLUSH_RECOMMENDED bit
  KVM: x86: hyper-v: Honor HV_X64_CLUSTER_IPI_RECOMMENDED bit
  KVM: x86: hyper-v: Honor HV_X64_EX_PROCESSOR_MASKS_RECOMMENDED bit
  KVM: selftests: move Hyper-V MSR definitions to hyperv.h
  KVM: selftests: Move evmcs.h to x86_64/
  KVM: selftests: Introduce hyperv_features test

 Documentation/virt/kvm/api.rst                |  11 +
 arch/x86/include/asm/kvm_host.h               |   9 +
 arch/x86/kvm/hyperv.c                         | 216 +++++-
 arch/x86/kvm/hyperv.h                         |   1 +
 arch/x86/kvm/x86.c                            |   4 +
 include/asm-generic/hyperv-tlfs.h             |   1 +
 include/uapi/linux/kvm.h                      |   1 +
 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../kvm/include/{ => x86_64}/evmcs.h          |   2 +-
 .../selftests/kvm/include/x86_64/hyperv.h     | 185 +++++
 .../selftests/kvm/x86_64/hyperv_clock.c       |   8 +-
 .../selftests/kvm/x86_64/hyperv_features.c    | 649 ++++++++++++++++++
 13 files changed, 1071 insertions(+), 18 deletions(-)
 rename tools/testing/selftests/kvm/include/{ => x86_64}/evmcs.h (99%)
 create mode 100644 tools/testing/selftests/kvm/include/x86_64/hyperv.h
 create mode 100644 tools/testing/selftests/kvm/x86_64/hyperv_features.c
```
