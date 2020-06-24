

#### [PATCH v3 0/2] target/arm: Fix using pmu=on on KVM
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
From patchwork Tue Jun 23 09:06:20 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 11620117
Return-Path: <SRS0=VBfj=AE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D16C5161F
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 09:06:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B726F20768
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 09:06:32 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Z3WPbkWa"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731887AbgFWJGb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 23 Jun 2020 05:06:31 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:41875 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1731853AbgFWJGb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 23 Jun 2020 05:06:31 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592903190;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
  content-type:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=2m2t021fPmocAk1w7rK7jsWgzV0rCiGfOdB2/ye3op0=;
        b=Z3WPbkWa0GYOkXZrKU+fTLtQfh/G+LQZweUSyTp/qomHywbrBC5UrxLh2cqApqwAMBV/3h
        NyYKDvU2mcQeuj1RzKHmqeSw6vaYrclqUcSyTs07KeiAgsUXso55j+Cyhe1hIZOes5kByT
        y/Gfy5npXwqTLlG0m+Dz//8YqcwOVuE=
Received: from mail-wr1-f71.google.com (mail-wr1-f71.google.com
 [209.85.221.71]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-333-T0zFWbBlPtu4sQnB7G7MKA-1; Tue, 23 Jun 2020 05:06:26 -0400
X-MC-Unique: T0zFWbBlPtu4sQnB7G7MKA-1
Received: by mail-wr1-f71.google.com with SMTP id y13so1388798wrp.13
        for <kvm@vger.kernel.org>; Tue, 23 Jun 2020 02:06:26 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=2m2t021fPmocAk1w7rK7jsWgzV0rCiGfOdB2/ye3op0=;
        b=Kxzq9TFWi9lUTNr8UdZE58C02WmGuerKUur6+ncKHZIa6nYNBDL7pOYOT0iFH2qm4Z
         ZGwZC4HWKuQgsSBM1OHHHulXNgFNNKSdR1DuL8+WUUd7wb/Z9RXdZhxARb3JfYYBzVMj
         qTE/XzxRCL3F9JKj/RNFyZcbBzzzGbD6KAwutDltAzhnjx3OOEYxUULFfxozK8jWEdn1
         0Qp+w9MxZBVNPzrg9ZEqS8qPZcG2QKKkCWud+vASlYIZAY4yFHUtHlREATHQky7RPqCA
         6iHpqTEXt6OJJ/oP0gx6HBpQ5FpWSQXo0RP37mRnjNqGgS0aInMxvp5v2eUgIzrhOFjN
         BpMw==
X-Gm-Message-State: AOAM532ykM8i+dRaJ623t7FOFphSyBOLT2Ubkhfchou7zT+N1HGPZ2eB
        W/Wkn6iVtCXYd/ux6kBYCPZk8cgxvDccMxgDN/X9/D44+YN2A0Yc5ikJXPwj7WbPPXW2MjS/rFs
        cpNNpb8D1WX4y
X-Received: by 2002:a05:6000:100c:: with SMTP id
 a12mr11437348wrx.81.1592903185144;
        Tue, 23 Jun 2020 02:06:25 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJyZP10WQPOHMp4i3NHPCCa9B8KmGvXoITH2SZ5LSo0WtmaCkCiIGpy/qn/H3k+WRHf/tocWQg==
X-Received: by 2002:a05:6000:100c:: with SMTP id
 a12mr11437320wrx.81.1592903184970;
        Tue, 23 Jun 2020 02:06:24 -0700 (PDT)
Received: from localhost.localdomain (1.red-83-51-162.dynamicip.rima-tde.net.
 [83.51.162.1])
        by smtp.gmail.com with ESMTPSA id
 b19sm2951554wmj.0.2020.06.23.02.06.23
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 23 Jun 2020 02:06:24 -0700 (PDT)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
To: qemu-devel@nongnu.org
Cc: qemu-arm@nongnu.org, Thomas Huth <thuth@redhat.com>,
 Paolo Bonzini <pbonzini@redhat.com>,
 Peter Maydell <peter.maydell@linaro.org>, kvm@vger.kernel.org,
 Andrew Jones <drjones@redhat.com>, Laurent Vivier <lvivier@redhat.com>,
	=?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
Subject: [PATCH v3 0/2] target/arm: Fix using pmu=on on KVM
Date: Tue, 23 Jun 2020 11:06:20 +0200
Message-Id: <20200623090622.30365-1-philmd@redhat.com>
X-Mailer: git-send-email 2.21.3
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Since v2:
- include Drew test fix (addressed Peter review comments)
- addressed Drew review comments
- collected R-b/A-b

Andrew Jones (1):
  tests/qtest/arm-cpu-features: Add feature setting tests

Philippe Mathieu-Daudé (1):
  target/arm: Check supported KVM features globally (not per vCPU)

 target/arm/kvm_arm.h           | 21 ++++++++-----------
 target/arm/cpu.c               |  2 +-
 target/arm/cpu64.c             | 10 ++++-----
 target/arm/kvm.c               |  4 ++--
 target/arm/kvm64.c             | 14 +++++--------
 tests/qtest/arm-cpu-features.c | 38 ++++++++++++++++++++++++++++++----
 6 files changed, 56 insertions(+), 33 deletions(-)
```
#### [PATCH 0/7] accel/kvm: Simplify few functions that can use global
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
From patchwork Tue Jun 23 10:50:45 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 11620297
Return-Path: <SRS0=VBfj=AE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9A23990
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 10:51:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 826FE20781
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 10:51:04 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="cRetiDK3"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732259AbgFWKvD (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 23 Jun 2020 06:51:03 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:25507 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1732254AbgFWKvC (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 23 Jun 2020 06:51:02 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592909460;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
  content-type:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=Q94CucqHN1D7KKGTyBIU8O5tt3pd+XQigNdMLEupMvs=;
        b=cRetiDK3/WA9O9IwNSfKC0Xe2NsNkYeaxAgqDPF2u0izGgMVqNNKxczv/3fa6q1/3ZX4Sx
        OA9yZ4Ci4xYx6lwmUcZki9AV5tQjim3UFEa+W6laYL89nv/vxHvPhrvAopDEg6PJ7bIjQL
        wjrcwF3q0F7sv4Lek6l5yfgp3x6CDW4=
Received: from mail-wr1-f70.google.com (mail-wr1-f70.google.com
 [209.85.221.70]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-193-761Z8lZHOdKBOFTVQBq1kg-1; Tue, 23 Jun 2020 06:50:57 -0400
X-MC-Unique: 761Z8lZHOdKBOFTVQBq1kg-1
Received: by mail-wr1-f70.google.com with SMTP id f5so14795876wrv.22
        for <kvm@vger.kernel.org>; Tue, 23 Jun 2020 03:50:56 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=Q94CucqHN1D7KKGTyBIU8O5tt3pd+XQigNdMLEupMvs=;
        b=HOinm9Qbl0QHBc8QmJFZGeYnCxQva2PDukwnxitiSj/sCGW+kaZgsptSlLn8GgLoaS
         B0K/2W8ANtwVDQAeH+Hpz6Ykvx4/ZXsR4tPBeueAKr3cHTXXIp0KTBJ4L/o/E12MDpIW
         nLP6b1skNMiflP5ndeRAPxdm6b18/7qsYGVOfIQYTqNgCQDlCXPA2h6gLIVK/Usc3MIW
         E9Dv4zRVPXFqGWyiT+TeTqay+zgPFXb5Pdj+q8zyxm1Ju7wnGY51phNi3yJD+YRQaZCE
         f1ZYIxaxsJsR87I2ACHqnUXW0wcHthhhgQAj/rvFZXIBJJYt75Fz/Q2+Y1BTfx4Md5MP
         Z8yQ==
X-Gm-Message-State: AOAM533LHZIdoHGF4Y99ln+4fJgYS+NmGokguJxYAwAdTDzlewWxzRm6
        IGfATTudUKHj85g0dvvdEgxvWb5luVNLUQlkG8lDmwvMFzUS8XjWgLQIgpYbZMoTZ08olJKVLXw
        1mfhezs8ps1iR
X-Received: by 2002:adf:f70e:: with SMTP id
 r14mr25942423wrp.150.1592909456037;
        Tue, 23 Jun 2020 03:50:56 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJwlFax+p3i5iqFekMZp1RI7Mb/GelsfigfVK2k+fsxbIpqx4pyzX+QN9QZ0xJFmneZKKMePoA==
X-Received: by 2002:adf:f70e:: with SMTP id
 r14mr25942396wrp.150.1592909455858;
        Tue, 23 Jun 2020 03:50:55 -0700 (PDT)
Received: from localhost.localdomain (1.red-83-51-162.dynamicip.rima-tde.net.
 [83.51.162.1])
        by smtp.gmail.com with ESMTPSA id
 r7sm3069566wmh.46.2020.06.23.03.50.54
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 23 Jun 2020 03:50:55 -0700 (PDT)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
To: qemu-devel@nongnu.org
Cc: Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>,
 Aurelien Jarno <aurelien@aurel32.net>, David Hildenbrand <david@redhat.com>,
 Christian Borntraeger <borntraeger@de.ibm.com>,
 Aleksandar Rikalo <aleksandar.rikalo@syrmia.com>,
 Richard Henderson <rth@twiddle.net>, qemu-s390x@nongnu.org,
 David Gibson <david@gibson.dropbear.id.au>,
 Peter Maydell <peter.maydell@linaro.org>,
 Eduardo Habkost <ehabkost@redhat.com>, kvm@vger.kernel.org,
 "Michael S. Tsirkin" <mst@redhat.com>, Halil Pasic <pasic@linux.ibm.com>,
 qemu-arm@nongnu.org, Cornelia Huck <cohuck@redhat.com>, qemu-ppc@nongnu.org,
 Marcel Apfelbaum <marcel.apfelbaum@gmail.com>,
 Paolo Bonzini <pbonzini@redhat.com>, Marcelo Tosatti <mtosatti@redhat.com>,
 Thomas Huth <thuth@redhat.com>,
 =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
Subject: [PATCH 0/7] accel/kvm: Simplify few functions that can use global
 kvm_state
Date: Tue, 23 Jun 2020 12:50:45 +0200
Message-Id: <20200623105052.1700-1-philmd@redhat.com>
X-Mailer: git-send-email 2.21.3
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Following Paolo's idea on kvm_check_extension():
https://www.mail-archive.com/qemu-devel@nongnu.org/msg713794.html

CI:
https://travis-ci.org/github/philmd/qemu/builds/701213438

Philippe Mathieu-Daudé (7):
  accel/kvm: Let kvm_check_extension use global KVM state
  accel/kvm: Simplify kvm_check_extension()
  accel/kvm: Simplify kvm_check_extension_list()
  accel/kvm: Simplify kvm_set_sigmask_len()
  target/i386/kvm: Simplify get_para_features()
  target/i386/kvm: Simplify kvm_get_mce_cap_supported()
  target/i386/kvm: Simplify kvm_get_supported_[feature]_msrs()

 include/sysemu/kvm.h         |  4 +-
 accel/kvm/kvm-all.c          | 76 +++++++++++++++----------------
 hw/hyperv/hyperv.c           |  2 +-
 hw/i386/kvm/clock.c          |  2 +-
 hw/i386/kvm/i8254.c          |  4 +-
 hw/i386/kvm/ioapic.c         |  2 +-
 hw/intc/arm_gic_kvm.c        |  2 +-
 hw/intc/openpic_kvm.c        |  2 +-
 hw/intc/xics_kvm.c           |  2 +-
 hw/s390x/s390-stattrib-kvm.c |  2 +-
 target/arm/kvm.c             | 13 +++---
 target/arm/kvm32.c           |  2 +-
 target/arm/kvm64.c           | 15 +++---
 target/i386/kvm.c            | 88 +++++++++++++++++-------------------
 target/mips/kvm.c            |  6 +--
 target/ppc/kvm.c             | 34 +++++++-------
 target/s390x/cpu_models.c    |  3 +-
 target/s390x/kvm.c           | 30 ++++++------
 18 files changed, 141 insertions(+), 148 deletions(-)
```
#### [PATCH v2 0/7] Refactor handling flow of SET_CPUID* 
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
From patchwork Tue Jun 23 11:58:09 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11620543
Return-Path: <SRS0=VBfj=AE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6E8CE618
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 11:59:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5D85620781
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 11:59:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732478AbgFWL6V (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 23 Jun 2020 07:58:21 -0400
Received: from mga05.intel.com ([192.55.52.43]:58474 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1732333AbgFWL6V (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 23 Jun 2020 07:58:21 -0400
IronPort-SDR: 
 PIlYuRk389QU4nB7axuXkyLlby9Pd0ObtWGRJI44Jj/0rfeDlUtsdyp7AJQzRPdmQEUntBkNJr
 zZ8TtICRBkpA==
X-IronPort-AV: E=McAfee;i="6000,8403,9660"; a="228710021"
X-IronPort-AV: E=Sophos;i="5.75,271,1589266800";
   d="scan'208";a="228710021"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga007.jf.intel.com ([10.7.209.58])
  by fmsmga105.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 23 Jun 2020 04:58:21 -0700
IronPort-SDR: 
 Bl9ke7FbJRHMn+rrIwBEbdYADJmeC7EVQg6ou+uNdm0TXzolbkxhl/Lye+UQPBNsnTp1zbfhTY
 6cX/OJSFmWog==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,271,1589266800";
   d="scan'208";a="285745012"
Received: from lxy-dell.sh.intel.com ([10.239.159.21])
  by orsmga007.jf.intel.com with ESMTP; 23 Jun 2020 04:58:18 -0700
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>
Cc: Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Xiaoyao Li <xiaoyao.li@intel.com>
Subject: [PATCH v2 0/7] Refactor handling flow of SET_CPUID* 
Date: Tue, 23 Jun 2020 19:58:09 +0800
Message-Id: <20200623115816.24132-1-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.18.2
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This serial is the extended version of
https://lkml.kernel.org/r/20200528151927.14346-1-xiaoyao.li@intel.com

First two patches are bug fixing, and the others aim to refactor the flow
of SET_CPUID* as:

1. cpuid check: check if userspace provides legal CPUID settings;

2. cpuid update: Update some special CPUID bits based on current vcpu
                 state, e.g., OSXSAVE, OSPKE, ...

3. update vcpu model: Update vcpu model (settings) based on the final CPUID
                      settings. 


v2:
 - rebase to kvm/queue: a037ff353ba6 ("Merge branch 'kvm-master' into HEAD")
 - change the name of kvm_update_state_based_on_cpuid() to
   kvm_update_vcpu_model() [Sean]
 - Add patch 5 to rename kvm_x86_ops.cpuid_date() to
   kvm_x86_ops.update_vcpu_model()

v1:
https://lkml.kernel.org/r/20200529085545.29242-1-xiaoyao.li@intel.com


Xiaoyao Li (7):
  KVM: X86: Reset vcpu->arch.cpuid_nent to 0 if SET_CPUID fails
  KVM: X86: Go on updating other CPUID leaves when leaf 1 is absent
  KVM: X86: Introduce kvm_check_cpuid()
  KVM: X86: Split kvm_update_cpuid()
  KVM: X86: Rename cpuid_update() to update_vcpu_model()
  KVM: X86: Move kvm_x86_ops.update_vcpu_model() into
    kvm_update_vcpu_model()
  KVM: X86: Move kvm_apic_set_version() to kvm_update_vcpu_model()

 arch/x86/include/asm/kvm_host.h |   2 +-
 arch/x86/kvm/cpuid.c            | 108 ++++++++++++++++++++------------
 arch/x86/kvm/cpuid.h            |   3 +-
 arch/x86/kvm/svm/svm.c          |   4 +-
 arch/x86/kvm/vmx/nested.c       |   2 +-
 arch/x86/kvm/vmx/vmx.c          |   4 +-
 arch/x86/kvm/x86.c              |   1 +
 7 files changed, 77 insertions(+), 47 deletions(-)
```
#### [PATCH v6 0/5] clean up redundant 'kvm_run' parameters
##### From: Tianjia Zhang <tianjia.zhang@linux.alibaba.com>

```c
From patchwork Tue Jun 23 13:14:13 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tianjia Zhang <tianjia.zhang@linux.alibaba.com>
X-Patchwork-Id: 11620679
Return-Path: <SRS0=VBfj=AE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 99DCE618
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 13:14:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8ADF2207E8
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 13:14:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732649AbgFWNO0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 23 Jun 2020 09:14:26 -0400
Received: from out30-130.freemail.mail.aliyun.com ([115.124.30.130]:42064
 "EHLO
        out30-130.freemail.mail.aliyun.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1732602AbgFWNO0 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 23 Jun 2020 09:14:26 -0400
X-Alimail-AntiSpam: 
 AC=PASS;BC=-1|-1;BR=01201311R171e4;CH=green;DM=||false|;DS=||;FP=0|-1|-1|-1|0|-1|-1|-1;HT=e01f04397;MF=tianjia.zhang@linux.alibaba.com;NM=1;PH=DS;RN=38;SR=0;TI=SMTPD_---0U0WFKzW_1592918058;
Received: from localhost(mailfrom:tianjia.zhang@linux.alibaba.com
 fp:SMTPD_---0U0WFKzW_1592918058)
          by smtp.aliyun-inc.com(127.0.0.1);
          Tue, 23 Jun 2020 21:14:18 +0800
From: Tianjia Zhang <tianjia.zhang@linux.alibaba.com>
To: pbonzini@redhat.com, tsbogend@alpha.franken.de, paulus@ozlabs.org,
        mpe@ellerman.id.au, benh@kernel.crashing.org,
        borntraeger@de.ibm.com, frankja@linux.ibm.com, david@redhat.com,
        cohuck@redhat.com, heiko.carstens@de.ibm.com, gor@linux.ibm.com,
        sean.j.christopherson@intel.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        tglx@linutronix.de, mingo@redhat.com, bp@alien8.de, x86@kernel.org,
        hpa@zytor.com, maz@kernel.org, james.morse@arm.com,
        julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
        christoffer.dall@arm.com, peterx@redhat.com, thuth@redhat.com,
        chenhuacai@gmail.com
Cc: kvm@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, linux-mips@vger.kernel.org,
        kvm-ppc@vger.kernel.org, linuxppc-dev@lists.ozlabs.org,
        linux-s390@vger.kernel.org, linux-kernel@vger.kernel.org,
        tianjia.zhang@linux.alibaba.com
Subject: [PATCH v6 0/5] clean up redundant 'kvm_run' parameters
Date: Tue, 23 Jun 2020 21:14:13 +0800
Message-Id: <20200623131418.31473-1-tianjia.zhang@linux.alibaba.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In the current kvm version, 'kvm_run' has been included in the 'kvm_vcpu'
structure. For historical reasons, many kvm-related function parameters
retain the 'kvm_run' and 'kvm_vcpu' parameters at the same time. This
patch does a unified cleanup of these remaining redundant parameters.

This series of patches has completely cleaned the architecture of
arm64, mips, ppc, and s390 (no such redundant code on x86). Due to
the large number of modified codes, a separate patch is made for each
platform. On the ppc platform, there is also a redundant structure
pointer of 'kvm_run' in 'vcpu_arch', which has also been cleaned
separately.
---
v6 changes:
  Rearrange patch sets, only keep the unmerged patch.
  rebase on mainline.

v5 change:
  ppc: fix for review.

v4 change:
  mips: fixes two errors in entry.c.

v3 change:
  Keep the existing `vcpu->run` in the function body unchanged.

v2 change:
  s390 retains the original variable name and minimizes modification.

Tianjia Zhang (5):
  KVM: s390: clean up redundant 'kvm_run' parameters
  KVM: arm64: clean up redundant 'kvm_run' parameters
  KVM: PPC: clean up redundant kvm_run parameters in assembly
  KVM: MIPS: clean up redundant 'kvm_run' parameters
  KVM: MIPS: clean up redundant kvm_run parameters in assembly

 arch/arm64/include/asm/kvm_coproc.h   |  12 +--
 arch/arm64/include/asm/kvm_host.h     |  11 +--
 arch/arm64/include/asm/kvm_mmu.h      |   2 +-
 arch/arm64/kvm/arm.c                  |   6 +-
 arch/arm64/kvm/handle_exit.c          |  36 ++++----
 arch/arm64/kvm/mmio.c                 |  11 +--
 arch/arm64/kvm/mmu.c                  |   5 +-
 arch/arm64/kvm/sys_regs.c             |  13 ++-
 arch/mips/include/asm/kvm_host.h      |  32 ++------
 arch/mips/kvm/emulate.c               |  59 +++++--------
 arch/mips/kvm/entry.c                 |  21 ++---
 arch/mips/kvm/mips.c                  |  14 ++--
 arch/mips/kvm/trap_emul.c             | 114 +++++++++++---------------
 arch/mips/kvm/vz.c                    |  26 +++---
 arch/powerpc/include/asm/kvm_ppc.h    |   2 +-
 arch/powerpc/kvm/book3s_interrupts.S  |  22 +++--
 arch/powerpc/kvm/book3s_pr.c          |   9 +-
 arch/powerpc/kvm/booke.c              |   9 +-
 arch/powerpc/kvm/booke_interrupts.S   |   9 +-
 arch/powerpc/kvm/bookehv_interrupts.S |  10 +--
 arch/s390/kvm/kvm-s390.c              |  23 ++++--
 21 files changed, 188 insertions(+), 258 deletions(-)
```
#### [PATCH v2 0/4] KVM: x86/mmu: Zapping and recycling cleanups
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Tue Jun 23 19:35:38 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11621585
Return-Path: <SRS0=VBfj=AE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5159114F6
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 19:36:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 38B7020B80
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 19:36:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387491AbgFWTfo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 23 Jun 2020 15:35:44 -0400
Received: from mga11.intel.com ([192.55.52.93]:11007 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1733309AbgFWTfn (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 23 Jun 2020 15:35:43 -0400
IronPort-SDR: 
 2mwWk0sby4tCvc0rJNa1K8Y8icUos6UEtcwxHT1zg1gc1A9xRDDO8r6YYFYy3NGNKXWNbZL8yj
 1+Sjxi+YBNbQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9661"; a="142430966"
X-IronPort-AV: E=Sophos;i="5.75,272,1589266800";
   d="scan'208";a="142430966"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga007.fm.intel.com ([10.253.24.52])
  by fmsmga102.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 23 Jun 2020 12:35:43 -0700
IronPort-SDR: 
 w6DCk5L9cIhRfbhUuZT1pBFGa7B7OXBCXGDP8PbeXVBFzTrGCpF+awJ71LdnnZorr4xA6xGRJ4
 xsY1D0eKysQA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,272,1589266800";
   d="scan'208";a="263428285"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by fmsmga007.fm.intel.com with ESMTP; 23 Jun 2020 12:35:43 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2 0/4] KVM: x86/mmu: Zapping and recycling cleanups
Date: Tue, 23 Jun 2020 12:35:38 -0700
Message-Id: <20200623193542.7554-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Semi-random, but related, changes that deal with the handling of active
root shadow pages during zapping and the zapping of arbitary/old pages.

Patch 1 changes the low level handling to keep zapped active roots off the
active page list.  KVM already relies on the vCPU to explicitly free the
root, putting invalid root pages back on the list is just a quirk of the
implementation.

Patches 2 reworks the MMU page recycling to batch zap pages instead of
zapping them one at a time.  This provides better handling for active root
pages and also avoids multiple remote TLB flushes.

Patch 3 applies the batch zapping to the .shrink_scan() path.  This is a
significant change in behavior, i.e. is the scariest of the changes, but
unless I'm missing something it provides the intended functionality that
has been lacking since shrinker support was first added.

Patch 4 changes the page fault handlers to return an error to userspace
instead of restarting the guest if there are no MMU pages available.  This
is dependent on patch 2 as theoretically the old recycling flow could
prematurely bail if it encountered an active root.

v2:
  - Add a comment for the list shenanigans in patch 1. [Paolo]
  - Add patches 2-4.
  - Rebased to kvm/queue, commit a037ff353ba6 ("Merge branch ...")

Sean Christopherson (4):
  KVM: x86/mmu: Don't put invalid SPs back on the list of active pages
  KVM: x86/mmu: Batch zap MMU pages when recycling oldest pages
  KVM: x86/mmu: Batch zap MMU pages when shrinking the slab
  KVM: x86/mmu: Exit to userspace on make_mmu_pages_available() error

 arch/x86/kvm/mmu/mmu.c         | 94 +++++++++++++++++++++-------------
 arch/x86/kvm/mmu/paging_tmpl.h |  3 +-
 2 files changed, 61 insertions(+), 36 deletions(-)
```
#### [PATCH 0/2] KVM: x86/mmu: Optimizations for kvm_get_mmu_page()
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Tue Jun 23 19:40:25 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11621601
Return-Path: <SRS0=VBfj=AE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A9488913
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 19:40:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9A5AA2081A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 23 Jun 2020 19:40:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387546AbgFWTkd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 23 Jun 2020 15:40:33 -0400
Received: from mga06.intel.com ([134.134.136.31]:64955 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1733248AbgFWTk3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 23 Jun 2020 15:40:29 -0400
IronPort-SDR: 
 01Y5N8SnWR25b2IwAMr71YQuHXtjkuoLhKeXdY4/zhgD4tXX6N4oLUrjPrqAIvt2OunIU/PeYT
 VwhAOX+q6LrA==
X-IronPort-AV: E=McAfee;i="6000,8403,9661"; a="205705216"
X-IronPort-AV: E=Sophos;i="5.75,272,1589266800";
   d="scan'208";a="205705216"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga003.fm.intel.com ([10.253.24.29])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 23 Jun 2020 12:40:28 -0700
IronPort-SDR: 
 S3TCBbfVG/Ul8arqWcMNB31+ytFBBI3PSAu9amcsKQri8ijG9Cb2pHW7sbdecBkyc+l/lRcQPb
 +c+JKBgkYdTg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,272,1589266800";
   d="scan'208";a="319249361"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by FMSMGA003.fm.intel.com with ESMTP; 23 Jun 2020 12:40:28 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Peter Feiner <pfeiner@google.com>,
        Jon Cargille <jcargill@google.com>
Subject: [PATCH 0/2] KVM: x86/mmu: Optimizations for kvm_get_mmu_page()
Date: Tue, 23 Jun 2020 12:40:25 -0700
Message-Id: <20200623194027.23135-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Avoid multiple hash lookups in kvm_get_mmu_page(), and tweak the cache
loop to optimize it for TDP.

Sean Christopherson (2):
  KVM: x86/mmu: Avoid multiple hash lookups in kvm_get_mmu_page()
  KVM: x86/mmu: Optimize MMU page cache lookup for fully direct MMUs

 arch/x86/kvm/mmu/mmu.c | 26 ++++++++++++++++----------
 1 file changed, 16 insertions(+), 10 deletions(-)
```
