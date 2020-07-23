

#### [PATCH v3 0/5] KVM_{GET,SET}_TSC_OFFSET ioctls
##### From: Oliver Upton <oupton@google.com>

```c
From patchwork Wed Jul 22 03:26:24 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Oliver Upton <oupton@google.com>
X-Patchwork-Id: 11677189
Return-Path: <SRS0=byMP=BB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2A9F913B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Jul 2020 03:26:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 11A2A207BB
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Jul 2020 03:26:44 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="gIDdgnMN"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731859AbgGVD0n (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 21 Jul 2020 23:26:43 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:33872 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1731781AbgGVD0m (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 21 Jul 2020 23:26:42 -0400
Received: from mail-pj1-x1049.google.com (mail-pj1-x1049.google.com
 [IPv6:2607:f8b0:4864:20::1049])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 8A306C061794
        for <kvm@vger.kernel.org>; Tue, 21 Jul 2020 20:26:42 -0700 (PDT)
Received: by mail-pj1-x1049.google.com with SMTP id k4so624376pjs.1
        for <kvm@vger.kernel.org>; Tue, 21 Jul 2020 20:26:42 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=8f11LQRDquKuMiFPe6+BACiHYk45SezXe4Dzf/I8q6U=;
        b=gIDdgnMNs+VR8E9uNl+dWnQ7GbI+ZPDxpHzPKyL3a4qix4mzg7BHKCRv7H67pIcP3v
         a4PjDqgyOyrKyTsGttc0+4U4jP0GwEyiYrlveCbVBqzobMKZsxJNmKFm97zMfZ7imeeP
         RwXvHvKrVOFPvy2DL8EU5TjDc9tV84A9k5e9ZvmamA6zQgneKJxl8T8Or7DGql2WFobQ
         YRXzO9kJY1n/CZKSCwUGoHsMwVYiZvZuGEXMfE6/xM4vuBsv/IQ2snvKfLeBGjhQm3Dh
         ui8rRPR3PoV2uZPTdENg5euw925+D8NFROfPAQDDfgluCs8EL4EfqtergPak3Tqz+iAD
         KLAw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=8f11LQRDquKuMiFPe6+BACiHYk45SezXe4Dzf/I8q6U=;
        b=og8ZGtcg5sGa1055Pb62WPu3u7TH/YfWsQmhpngu752Mhu6gwdAExaJXunozijNS7W
         B8WYeOzhUbooN6JdJj2dSDfMSEV73jN/ce4P158EaL4Y5s2NRzSjkenx+5EFIf89cX50
         wAdVnswlpzJCjbUppm+txhf090lfT1oU+FJz9zHRANVgLrAeg4MEvZfI2u/4WhNgLPKT
         J7FBxaRKcr/4qHc0hs1r7Nu2jJPSGL3WP4tkBF6pM1wMschU+L9pIEkzghkMhpv4CF+r
         DIQprgzB/Xa9on60z6bo1gG10BF4A/XW7PmKu+t8uXrMlnQcvR1QspHTyAwGJmFank+Y
         15dA==
X-Gm-Message-State: AOAM531Dw8LGuCXJQFMryMAF1O25NC2nZlSU7aKoBk7rOIGXquPZye8g
        Bvsl7cWfeSC2R3Ztpz61bRhTec1Ny47oCjZVOeI2zMF3RuMXPRWN+mebRczxX3H5oppsGv2H9yW
        KnUte/JffTp0/8Q8WswktZcztOgpA85JXRVqa2OWNBxLdUgDkRUEi5/4dmQ==
X-Google-Smtp-Source: 
 ABdhPJw1U8f7yFISRUxehIDZqzFSsmWJlKf3RnZkQvTgcdTETzW6neSxCOCxc1E5WAOTiOtx3x/wA15iu/4=
X-Received: by 2002:a62:52cd:: with SMTP id
 g196mr26998369pfb.178.1595388401915;
 Tue, 21 Jul 2020 20:26:41 -0700 (PDT)
Date: Wed, 22 Jul 2020 03:26:24 +0000
Message-Id: <20200722032629.3687068-1-oupton@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.28.0.rc0.142.g3c755180ce-goog
Subject: [PATCH v3 0/5] KVM_{GET,SET}_TSC_OFFSET ioctls
From: Oliver Upton <oupton@google.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Peter Shier <pshier@google.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Peter Hornyack <peterhornyack@google.com>,
        Oliver Upton <oupton@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

To date, VMMs have typically restored the guest's TSCs by value using
the KVM_SET_MSRS ioctl for each vCPU. However, restoring the TSCs by
value introduces some challenges with synchronization as the TSCs
continue to tick throughout the restoration process. As such, KVM has
some heuristics around TSC writes to infer whether or not the guest or
host is attempting to synchronize the TSCs.

Instead of guessing at the intentions of a VMM, it'd be better to
provide an interface that allows for explicit synchronization of the
guest's TSCs. To that end, this series introduces the
KVM_{GET,SET}_TSC_OFFSET ioctls, yielding control of the TSC offset to
userspace.

v2 => v3:
 - Mark kvm_write_tsc_offset() as static (whoops)

v1 => v2:
 - Added clarification to the documentation of KVM_SET_TSC_OFFSET to
   indicate that it can be used instead of an IA32_TSC MSR restore
   through KVM_SET_MSRS
 - Fixed KVM_SET_TSC_OFFSET to participate in the existing TSC
   synchronization heuristics, thereby enabling the KVM masterclock when
   all vCPUs are in phase.

Oliver Upton (4):
  kvm: x86: refactor masterclock sync heuristics out of kvm_write_tsc
  kvm: vmx: check tsc offsetting with nested_cpu_has()
  selftests: kvm: use a helper function for reading cpuid
  selftests: kvm: introduce tsc_offset_test

Peter Hornyack (1):
  kvm: x86: add KVM_{GET,SET}_TSC_OFFSET ioctls

 Documentation/virt/kvm/api.rst                |  31 ++
 arch/x86/include/asm/kvm_host.h               |   1 +
 arch/x86/kvm/vmx/vmx.c                        |   2 +-
 arch/x86/kvm/x86.c                            | 147 ++++---
 include/uapi/linux/kvm.h                      |   5 +
 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../testing/selftests/kvm/include/test_util.h |   3 +
 .../selftests/kvm/include/x86_64/processor.h  |  15 +
 .../selftests/kvm/include/x86_64/svm_util.h   |  10 +-
 .../selftests/kvm/include/x86_64/vmx.h        |   9 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |   1 +
 tools/testing/selftests/kvm/lib/x86_64/vmx.c  |  11 +
 .../selftests/kvm/x86_64/tsc_offset_test.c    | 362 ++++++++++++++++++
 14 files changed, 550 insertions(+), 49 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/tsc_offset_test.c
```
#### [PATCH V3 0/6] IRQ offloading for vDPA
##### From: Zhu Lingshan <lingshan.zhu@live.com>

```c
From patchwork Wed Jul 22 09:49:04 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@live.com>
X-Patchwork-Id: 11678027
Return-Path: <SRS0=byMP=BB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A371413B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Jul 2020 09:53:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 925DF20729
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Jul 2020 09:53:08 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731424AbgGVJxG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 22 Jul 2020 05:53:06 -0400
Received: from mga18.intel.com ([134.134.136.126]:63311 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726147AbgGVJxG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 22 Jul 2020 05:53:06 -0400
IronPort-SDR: 
 ZDEEjv6F7/YUYAKCvnGdZiu66YBAuNsNT0wjyaW3Bqp14+1xprVCbIW8i0gZ9ERxZO7Ax2fwr1
 Cl9WuqwMbT1Q==
X-IronPort-AV: E=McAfee;i="6000,8403,9689"; a="137804228"
X-IronPort-AV: E=Sophos;i="5.75,381,1589266800";
   d="scan'208";a="137804228"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga006.fm.intel.com ([10.253.24.20])
  by orsmga106.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 22 Jul 2020 02:53:05 -0700
IronPort-SDR: 
 7KJ6UsqeyYgkOsvhtp/wSxLkEzP18miCfz/0UJI3ez1eKMFvPQl61uRoMNNqaev27ltyVyXZ2L
 zltqv2RWcwoA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,381,1589266800";
   d="scan'208";a="487936068"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.192.131])
  by fmsmga006.fm.intel.com with ESMTP; 22 Jul 2020 02:53:02 -0700
From: Zhu Lingshan <lingshan.zhu@live.com>
To: jasowang@redhat.com, alex.williamson@redhat.com, mst@redhat.com,
        pbonzini@redhat.com, sean.j.christopherson@intel.com,
        wanpengli@tencent.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, Zhu Lingshan <lingshan.zhu@live.com>
Subject: [PATCH V3 0/6] IRQ offloading for vDPA
Date: Wed, 22 Jul 2020 17:49:04 +0800
Message-Id: <20200722094910.218014-1-lingshan.zhu@live.com>
X-Mailer: git-send-email 2.18.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series intends to implement IRQ offloading for
vhost_vdpa.

By the feat of irq forwarding facilities like posted
interrupt on X86, irq bypass can  help deliver
interrupts to vCPU directly.

vDPA devices have dedicated hardware backends like VFIO
pass-throughed devices. So it would be possible to setup
irq offloading(irq bypass) for vDPA devices and gain
performance improvements.

In my testing, with this feature, we can save 0.1ms
in a ping between two VFs on average.

changes from V2:
(1)rename struct vhost_call_ctx to vhost_vring_call
(2)add kvm_arch_end_assignment() in del_producer()
code path
(3)rename vDPA helpers to vdpa_devm_request_irq()
and vdpa_devm_free_irq(). Add better comments
for them.
(4)better comments for setup_vq_irq() and
unsetup_vq_irq()
(5)In vDPA VHOST_SET_VRING_CALL, will call vhost_vdpa_update_vq_irq()
without checking producer.irq, move this check into
vhost_vdpa_update_vq_irq(), so that get advantage of the spinlock.
(6)Add a function vhost_vdpa_clean_irq(), this function will unregister
the producer of vqs when vhost_vdpa_release(). This is safe
for control vq.
(7) minor improvements

changes from V1:
(1)dropped vfio changes.
(3)removed KVM_HVAE_IRQ_BYPASS checks
(4)locking fixes
(5)simplified vhost_vdpa_update_vq_irq()
(6)minor improvements

Zhu Lingshan (6):
  vhost: introduce vhost_vring_call
  kvm: detect assigned device via irqbypass manager
  vDPA: implement vq IRQ allocate/free helpers in vDPA core
  vhost_vdpa: implement IRQ offloading in vhost_vdpa
  ifcvf: replace irq_request/free with vDPA helpers
  irqbypass: do not start cons/prod when failed connect

 arch/x86/kvm/x86.c              | 11 +++++-
 drivers/vdpa/ifcvf/ifcvf_main.c | 14 ++++---
 drivers/vdpa/vdpa.c             | 49 +++++++++++++++++++++++
 drivers/vhost/Kconfig           |  1 +
 drivers/vhost/vdpa.c            | 70 +++++++++++++++++++++++++++++++--
 drivers/vhost/vhost.c           | 22 ++++++++---
 drivers/vhost/vhost.h           |  9 ++++-
 include/linux/vdpa.h            | 13 ++++++
 virt/lib/irqbypass.c            | 16 +++++---
 9 files changed, 182 insertions(+), 23 deletions(-)
```
#### [PATCH V3 0/6] IRQ offloading for vDPA
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
From patchwork Wed Jul 22 10:08:53 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 11678087
Return-Path: <SRS0=byMP=BB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E4E29618
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Jul 2020 10:12:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D55D1206F5
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Jul 2020 10:12:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731378AbgGVKM5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 22 Jul 2020 06:12:57 -0400
Received: from mga03.intel.com ([134.134.136.65]:1548 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726153AbgGVKM4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 22 Jul 2020 06:12:56 -0400
IronPort-SDR: 
 xeW5ChbJpf/r2hLVs7ISik6HeAoNHCNeqlodkZVFrBw66srS79v/OMA6s9bG+w+GGqiXcEf9yy
 DqTodx/xuXQw==
X-IronPort-AV: E=McAfee;i="6000,8403,9689"; a="150280654"
X-IronPort-AV: E=Sophos;i="5.75,381,1589266800";
   d="scan'208";a="150280654"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 22 Jul 2020 03:12:54 -0700
IronPort-SDR: 
 3QwdtUb5jyy1VyXx3+rx0BvLTgUOlHZ1VO/vqj1UQFRCT+GJKpUvYEVZomzh8cizIj1UYv4svO
 Ee192DZAK1zg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,381,1589266800";
   d="scan'208";a="392634853"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.192.131])
  by fmsmga001.fm.intel.com with ESMTP; 22 Jul 2020 03:12:52 -0700
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: jasowang@redhat.com, alex.williamson@redhat.com, mst@redhat.com,
        pbonzini@redhat.com, sean.j.christopherson@intel.com,
        wanpengli@tencent.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH V3 0/6] IRQ offloading for vDPA
Date: Wed, 22 Jul 2020 18:08:53 +0800
Message-Id: <20200722100859.221669-1-lingshan.zhu@intel.com>
X-Mailer: git-send-email 2.18.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series intends to implement IRQ offloading for
vhost_vdpa.

By the feat of irq forwarding facilities like posted
interrupt on X86, irq bypass can  help deliver
interrupts to vCPU directly.

vDPA devices have dedicated hardware backends like VFIO
pass-throughed devices. So it would be possible to setup
irq offloading(irq bypass) for vDPA devices and gain
performance improvements.

In my testing, with this feature, we can save 0.1ms
in a ping between two VFs on average.

changes from V2:
(1)rename struct vhost_call_ctx to vhost_vring_call
(2)add kvm_arch_end_assignment() in del_producer()
code path
(3)rename vDPA helpers to vdpa_devm_request_irq()
and vdpa_devm_free_irq(). Add better comments
for them.
(4)better comments for setup_vq_irq() and
unsetup_vq_irq()
(5)In vDPA VHOST_SET_VRING_CALL, will call vhost_vdpa_update_vq_irq()
without checking producer.irq, move this check into
vhost_vdpa_update_vq_irq(), so that get advantage of the spinlock.
(6)Add a function vhost_vdpa_clean_irq(), this function will unregister
the producer of vqs when vhost_vdpa_release(). This is safe
for control vq.
(7) minor improvements

changes from V1:
(1)dropped vfio changes.
(3)removed KVM_HVAE_IRQ_BYPASS checks
(4)locking fixes
(5)simplified vhost_vdpa_updat

Zhu Lingshan (6):
  vhost: introduce vhost_vring_call
  kvm: detect assigned device via irqbypass manager
  vDPA: implement vq IRQ allocate/free helpers in vDPA core
  vhost_vdpa: implement IRQ offloading in vhost_vdpa
  ifcvf: replace irq_request/free with vDPA helpers
  irqbypass: do not start cons/prod when failed connect

 arch/x86/kvm/x86.c              | 11 +++++-
 drivers/vdpa/ifcvf/ifcvf_main.c | 14 ++++---
 drivers/vdpa/vdpa.c             | 49 +++++++++++++++++++++++
 drivers/vhost/Kconfig           |  1 +
 drivers/vhost/vdpa.c            | 70 +++++++++++++++++++++++++++++++--
 drivers/vhost/vhost.c           | 22 ++++++++---
 drivers/vhost/vhost.h           |  9 ++++-
 include/linux/vdpa.h            | 13 ++++++
 virt/lib/irqbypass.c            | 16 +++++---
 9 files changed, 182 insertions(+), 23 deletions(-)
```
#### [PATCH v4 0/4] Add a vhost RPMsg API
##### From: Guennadi Liakhovetski <guennadi.liakhovetski@linux.intel.com>

```c
From patchwork Wed Jul 22 15:09:23 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Guennadi Liakhovetski
 <guennadi.liakhovetski@linux.intel.com>
X-Patchwork-Id: 11678623
Return-Path: <SRS0=byMP=BB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D2110618
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Jul 2020 15:09:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BA51B20709
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Jul 2020 15:09:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728086AbgGVPJe (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 22 Jul 2020 11:09:34 -0400
Received: from mga14.intel.com ([192.55.52.115]:33983 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726717AbgGVPJd (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 22 Jul 2020 11:09:33 -0400
IronPort-SDR: 
 Ml1NjBay97GwnoP1wIeApPISk1NtazU+TINFB0U91IwPseki9ytL2LH4A0Kc3EuRJrVmlbXrPt
 yjrUXZIgYniw==
X-IronPort-AV: E=McAfee;i="6000,8403,9689"; a="149513597"
X-IronPort-AV: E=Sophos;i="5.75,383,1589266800";
   d="scan'208";a="149513597"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by fmsmga103.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 22 Jul 2020 08:09:31 -0700
IronPort-SDR: 
 RlU5InFR7sDN5rcYvVgCLEpYmQ+Gd8aXOFnMbhPL0hxvuYvKnv3StrJqA1UIpEvc5pg372xPXs
 tzqQod9sFYFg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,383,1589266800";
   d="scan'208";a="432407239"
Received: from gliakhov-mobl2.ger.corp.intel.com (HELO
 ubuntu.ger.corp.intel.com) ([10.252.58.190])
  by orsmga004.jf.intel.com with ESMTP; 22 Jul 2020 08:09:28 -0700
From: Guennadi Liakhovetski <guennadi.liakhovetski@linux.intel.com>
To: kvm@vger.kernel.org
Cc: linux-remoteproc@vger.kernel.org,
        virtualization@lists.linux-foundation.org,
        sound-open-firmware@alsa-project.org,
        Pierre-Louis Bossart <pierre-louis.bossart@linux.intel.com>,
        Liam Girdwood <liam.r.girdwood@linux.intel.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        Ohad Ben-Cohen <ohad@wizery.com>,
        Bjorn Andersson <bjorn.andersson@linaro.org>,
        Mathieu Poirier <mathieu.poirier@linaro.org>,
        Vincent Whitchurch <vincent.whitchurch@axis.com>
Subject: [PATCH v4 0/4] Add a vhost RPMsg API
Date: Wed, 22 Jul 2020 17:09:23 +0200
Message-Id: <20200722150927.15587-1-guennadi.liakhovetski@linux.intel.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

Now that virtio-rpmsg endianness fixes have been merged we can 
proceed with the next step.

v4:
- add endianness conversions to comply with the VirtIO standard

v3:
- address several checkpatch warnings
- address comments from Mathieu Poirier

v2:
- update patch #5 with a correct vhost_dev_init() prototype
- drop patch #6 - it depends on a different patch, that is currently
  an RFC
- address comments from Pierre-Louis Bossart:
  * remove "default n" from Kconfig

Linux supports RPMsg over VirtIO for "remote processor" / AMP use
cases. It can however also be used for virtualisation scenarios,
e.g. when using KVM to run Linux on both the host and the guests.
This patch set adds a wrapper API to facilitate writing vhost
drivers for such RPMsg-based solutions. The first use case is an
audio DSP virtualisation project, currently under development, ready
for review and submission, available at
https://github.com/thesofproject/linux/pull/1501/commits

Thanks
Guennadi

Guennadi Liakhovetski (4):
  vhost: convert VHOST_VSOCK_SET_RUNNING to a generic ioctl
  rpmsg: move common structures and defines to headers
  rpmsg: update documentation
  vhost: add an RPMsg API

 Documentation/rpmsg.txt          |   6 +-
 drivers/rpmsg/virtio_rpmsg_bus.c |  78 +------
 drivers/vhost/Kconfig            |   7 +
 drivers/vhost/Makefile           |   3 +
 drivers/vhost/rpmsg.c            | 375 +++++++++++++++++++++++++++++++
 drivers/vhost/vhost_rpmsg.h      |  74 ++++++
 include/linux/virtio_rpmsg.h     |  83 +++++++
 include/uapi/linux/rpmsg.h       |   3 +
 include/uapi/linux/vhost.h       |   4 +-
 9 files changed, 553 insertions(+), 80 deletions(-)
 create mode 100644 drivers/vhost/rpmsg.c
 create mode 100644 drivers/vhost/vhost_rpmsg.h
 create mode 100644 include/linux/virtio_rpmsg.h
```
#### [RFC PATCH v1 00/34] VM introspection - EPT Views and Virtualization
##### From: =?utf-8?q?Adalbert_Laz=C4=83r?= <alazar@bitdefender.com>

```c
From patchwork Wed Jul 22 16:00:47 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Adalbert_Laz=C4=83r?=
 <alazar@bitdefender.com>
X-Patchwork-Id: 11678831
Return-Path: <SRS0=byMP=BB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8CFA114E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Jul 2020 16:01:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7EA3B20717
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Jul 2020 16:01:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728910AbgGVQBg (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 22 Jul 2020 12:01:36 -0400
Received: from mx01.bbu.dsd.mx.bitdefender.com ([91.199.104.161]:37814 "EHLO
        mx01.bbu.dsd.mx.bitdefender.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726349AbgGVQBf (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 22 Jul 2020 12:01:35 -0400
Received: from smtp.bitdefender.com (smtp01.buh.bitdefender.com [10.17.80.75])
        by mx01.bbu.dsd.mx.bitdefender.com (Postfix) with ESMTPS id
 D913A3016E60;
        Wed, 22 Jul 2020 19:01:31 +0300 (EEST)
Received: from localhost.localdomain (unknown [91.199.104.6])
        by smtp.bitdefender.com (Postfix) with ESMTPSA id CC0553072784;
        Wed, 22 Jul 2020 19:01:31 +0300 (EEST)
From: =?utf-8?q?Adalbert_Laz=C4=83r?= <alazar@bitdefender.com>
To: kvm@vger.kernel.org
Cc: virtualization@lists.linux-foundation.org,
 Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?q?Adalbert_Laz=C4=83r?= <alazar@bitdefender.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [RFC PATCH v1 00/34] VM introspection - EPT Views and Virtualization
 Exceptions
Date: Wed, 22 Jul 2020 19:00:47 +0300
Message-Id: <20200722160121.9601-1-alazar@bitdefender.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch series is based on the VM introspection patches
(https://lore.kernel.org/kvm/20200721210922.7646-1-alazar@bitdefender.com/),
extending the introspection API with EPT Views and Virtualization
Exceptions (#VE) support.

The purpose of this series is to get an initial feedback and to see if
we are on the right track, especially because the changes made to add
the EPT views are not small (even if they add support only for different
access rights for now, not for different content).

One use case for these extensions is to run a guest agent, isolated in
another EPT view and using Virtualization Exceptions (#VE), to reduce
the number of VM-Exits caused by EPT violations.

Another case for EPT views is to single-step one vCPU on a different view
(with more relaxed page access restrictions) while all the others run
on a main/restricted view.

Patches 1-11 make preparatory changes for EPT views.

Patches 12-19 extend the VM introspection API with EPT-views related
commands and data. The Get/Set/Control EPT view commands are added,
the KVMI_VM_SET_PAGE_ACCESS command and the vCPU introspection events
are extended with the EPT view.

Patches 20-30 make preparatory changes for #VE.

Patches 31-34 extend the VM introspection API with #VE related commands.

Adalbert Lazăr (2):
  KVM: x86: mmu: reindent to avoid lines longer than 80 chars
  KVM: introspection: mask out non-rwx flags when reading/writing
    from/to the internal database

Marian Rotariu (5):
  KVM: x86: export .get_vmfunc_status()
  KVM: x86: export .get_eptp_switching_status()
  KVM: x86: mmu: add support for EPT switching
  KVM: x86: add .set_ept_view()
  KVM: x86: vmx: add support for virtualization exceptions

Sean Christopherson (2):
  KVM: VMX: Define EPT suppress #VE bit (bit 63 in EPT leaf entries)
  KVM: VMX: Suppress EPT violation #VE by default (when enabled)

Ștefan Șicleru (25):
  KVM: x86: add kvm_get_ept_view()
  KVM: x86: mmu: add EPT view parameter to kvm_mmu_get_page()
  KVM: x86: mmu: increase mmu_memory_cache size
  KVM: x86: add .control_ept_view()
  KVM: x86: page track: allow page tracking for different EPT views
  KVM: x86: mmu: allow zapping shadow pages for specific EPT views
  KVM: introspection: extend struct kvmi_features with the EPT views
    status support
  KVM: introspection: add KVMI_VCPU_GET_EPT_VIEW
  KVM: introspection: add 'view' field to struct kvmi_event_arch
  KVM: introspection: add KVMI_VCPU_SET_EPT_VIEW
  KVM: introspection: add KVMI_VCPU_CONTROL_EPT_VIEW
  KVM: introspection: extend the access rights database with EPT view
    info
  KVM: introspection: extend KVMI_VM_SET_PAGE_ACCESS with EPT view info
  KVM: introspection: clean non-default EPTs on unhook
  KVM: x86: mmu: fix: update present_mask in spte_read_protect()
  KVM: vmx: trigger vm-exits for mmio sptes by default when #VE is
    enabled
  KVM: x86: svm: set .clear_page()
  KVM: x86: add .set_ve_info()
  KVM: x86: add .disable_ve()
  KVM: x86: page_track: add support for suppress #VE bit
  KVM: vmx: make use of EPTP_INDEX in vmx_handle_exit()
  KVM: vmx: make use of EPTP_INDEX in vmx_set_ept_view()
  KVM: introspection: add #VE host capability checker
  KVM: introspection: add KVMI_VCPU_SET_VE_INFO/KVMI_VCPU_DISABLE_VE
  KVM: introspection: add KVMI_VM_SET_PAGE_SVE

 Documentation/virt/kvm/kvmi.rst               | 227 +++++++++++-
 arch/x86/include/asm/kvm_host.h               |  27 +-
 arch/x86/include/asm/kvm_page_track.h         |   5 +-
 arch/x86/include/asm/kvmi_host.h              |   1 +
 arch/x86/include/asm/vmx.h                    |   5 +
 arch/x86/include/uapi/asm/kvmi.h              |  44 ++-
 arch/x86/kvm/Makefile                         |   2 +-
 arch/x86/kvm/kvmi.c                           |  83 ++++-
 arch/x86/kvm/mmu.h                            |  12 +-
 arch/x86/kvm/mmu/mmu.c                        | 191 +++++++---
 arch/x86/kvm/mmu/page_track.c                 |  63 ++--
 arch/x86/kvm/mmu/paging_tmpl.h                |   6 +-
 arch/x86/kvm/svm/svm.c                        |   1 +
 arch/x86/kvm/vmx/capabilities.h               |  13 +
 arch/x86/kvm/vmx/clear_page.S                 |  17 +
 arch/x86/kvm/vmx/vmx.c                        | 291 ++++++++++++++-
 arch/x86/kvm/vmx/vmx.h                        |  18 +
 arch/x86/kvm/x86.c                            |  20 +-
 drivers/gpu/drm/i915/gvt/kvmgt.c              |   8 +-
 include/linux/kvmi_host.h                     |   2 +-
 include/uapi/linux/kvmi.h                     |  12 +-
 .../testing/selftests/kvm/x86_64/kvmi_test.c  | 335 +++++++++++++++++-
 virt/kvm/introspection/kvmi.c                 | 175 ++++++---
 virt/kvm/introspection/kvmi_int.h             |  17 +-
 virt/kvm/introspection/kvmi_msg.c             | 106 ++++++
 25 files changed, 1512 insertions(+), 169 deletions(-)
 create mode 100644 arch/x86/kvm/vmx/clear_page.S


base-commit: d9da9f5842e0697564f0f3e586d858f2626e8f92
Based-on: <20200721210922.7646-1-alazar@bitdefender.com>
CC: Sean Christopherson <sean.j.christopherson@intel.com>
```
#### [patch V5 00/15] entry, x86, kvm: Generic entry/exit functionality
##### From: Thomas Gleixner <tglx@linutronix.de>

```c
From patchwork Wed Jul 22 21:59:54 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Gleixner <tglx@linutronix.de>
X-Patchwork-Id: 11679287
Return-Path: <SRS0=byMP=BB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 035366C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Jul 2020 22:14:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DBBEE22B43
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Jul 2020 22:14:28 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=linutronix.de header.i=@linutronix.de
 header.b="G7gFd1y4";
	dkim=permerror (0-bit key) header.d=linutronix.de header.i=@linutronix.de
 header.b="miICDflK"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1733079AbgGVWL1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 22 Jul 2020 18:11:27 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:39128 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1733043AbgGVWL0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 22 Jul 2020 18:11:26 -0400
Received: from galois.linutronix.de (Galois.linutronix.de
 [IPv6:2a0a:51c0:0:12e:550::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id C80ACC0619DC;
        Wed, 22 Jul 2020 15:11:24 -0700 (PDT)
Message-Id: <20200722215954.464281930@linutronix.de>
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=linutronix.de;
        s=2020; t=1595455882;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:content-transfer-encoding:content-transfer-encoding;
        bh=ahlK79PK5YUaQAhd7lygE8UJdfTKv0Vu+HW5xnc5ELM=;
        b=G7gFd1y4nAOmB1fa4bznNO6Hn3Xz5vGns+k1b2AAzgB3r8aFNsAxK66jM7k+woJjeVIGPk
        98ntp/LIG2+BVCPqkuHjXZQI75CRxyf81EpjyYchX1/id1bgwygapu4zV6NpZj5iV+34lN
        5jupVlM/5oMJUto46ob0x4SNkXVFEdZ/4vVsJBiX7zlSsHAjQy9gxt5C0toWs91Bpe/RZs
        L185WibgR0N4V4qXYAj4nyjC7PSyi9i1q0vQ+1ut7dpat2CwoFRTkp6RJ+x9moWliHMRCE
        h3QD1iopZgNwAdQKa8R+EDTF0w281Ry2bTenti8lF/lPd6GforcDq/MMnNnnZQ==
DKIM-Signature: v=1; a=ed25519-sha256; c=relaxed/relaxed; d=linutronix.de;
        s=2020e; t=1595455882;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:content-transfer-encoding:content-transfer-encoding;
        bh=ahlK79PK5YUaQAhd7lygE8UJdfTKv0Vu+HW5xnc5ELM=;
        b=miICDflKl+rPTMgRosTGj5rJ8+uSXdXfY8WUsObaLLnl8ki5Ojwpope+EfNnupX4TEtU3L
        iAM7h9QaqHryhDDQ==
Date: Wed, 22 Jul 2020 23:59:54 +0200
From: Thomas Gleixner <tglx@linutronix.de>
To: LKML <linux-kernel@vger.kernel.org>
Cc: x86@kernel.org, linux-arch@vger.kernel.org,
        Will Deacon <will@kernel.org>, Arnd Bergmann <arnd@arndb.de>,
        Mark Rutland <mark.rutland@arm.com>,
        Kees Cook <keescook@chromium.org>,
        Keno Fischer <keno@juliacomputing.com>,
        Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org,
        Gabriel Krisman Bertazi <krisman@collabora.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [patch V5 00/15] entry, x86, kvm: Generic entry/exit functionality
 for host and guest
Content-transfer-encoding: 8-bit
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is the 5th version of generic entry/exit functionality for host and
guest.

The 4th version is available here:

    https://lore.kernel.org/r/20200721105706.030914876@linutronix.de

Changes vs. V4:

  - Add the missing instrumentation prevetions to the entry Makefile (Kees)
  - Rename exit_to_guest to xfer_to_guest (Sean)

The patches depend on:

    git://git.kernel.org/pub/scm/linux/kernel/git/tip/tip.git x86/entry

The lot is also available from git:

    git://git.kernel.org/pub/scm/linux/kernel/git/tglx/devel.git x86/entry

Thanks,

	tglx
```
