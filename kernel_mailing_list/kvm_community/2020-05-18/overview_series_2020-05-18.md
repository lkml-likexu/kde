#### [PATCH Kernel v22 1/8] vfio: UAPI for migration interface for device state
##### From: Kirti Wankhede <kwankhede@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kirti Wankhede <kwankhede@nvidia.com>
X-Patchwork-Id: 11554789
Return-Path: <SRS0=OZeJ=7A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id ACF24912
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 May 2020 06:29:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8FB5C207C4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 May 2020 06:29:58 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="WizfX8YD"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726628AbgERG35 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 18 May 2020 02:29:57 -0400
Received: from hqnvemgate25.nvidia.com ([216.228.121.64]:7836 "EHLO
        hqnvemgate25.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726432AbgERG35 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 18 May 2020 02:29:57 -0400
Received: from hqpgpgate101.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate25.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5ec22b170000>; Sun, 17 May 2020 23:28:39 -0700
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate101.nvidia.com (PGP Universal service);
  Sun, 17 May 2020 23:29:57 -0700
X-PGP-Universal: processed;
        by hqpgpgate101.nvidia.com on Sun, 17 May 2020 23:29:57 -0700
Received: from HQMAIL105.nvidia.com (172.20.187.12) by HQMAIL101.nvidia.com
 (172.20.187.10) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Mon, 18 May
 2020 06:29:56 +0000
Received: from kwankhede-dev.nvidia.com (10.124.1.5) by HQMAIL105.nvidia.com
 (172.20.187.12) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Mon, 18 May 2020 06:29:50 +0000
From: Kirti Wankhede <kwankhede@nvidia.com>
To: <alex.williamson@redhat.com>, <cjia@nvidia.com>
CC: <kevin.tian@intel.com>, <ziye.yang@intel.com>,
        <changpeng.liu@intel.com>, <yi.l.liu@intel.com>,
        <mlevitsk@redhat.com>, <eskultet@redhat.com>, <cohuck@redhat.com>,
        <dgilbert@redhat.com>, <jonathan.davies@nutanix.com>,
        <eauger@redhat.com>, <aik@ozlabs.ru>, <pasic@linux.ibm.com>,
        <felipe@nutanix.com>, <Zhengxiao.zx@Alibaba-inc.com>,
        <shuangtai.tst@alibaba-inc.com>, <Ken.Xue@amd.com>,
        <zhi.a.wang@intel.com>, <yan.y.zhao@intel.com>,
        <qemu-devel@nongnu.org>, <kvm@vger.kernel.org>,
        "Kirti Wankhede" <kwankhede@nvidia.com>
Subject: [PATCH Kernel v22 1/8] vfio: UAPI for migration interface for device
 state
Date: Mon, 18 May 2020 11:26:30 +0530
Message-ID: <1589781397-28368-2-git-send-email-kwankhede@nvidia.com>
X-Mailer: git-send-email 2.7.0
In-Reply-To: <1589781397-28368-1-git-send-email-kwankhede@nvidia.com>
References: <1589781397-28368-1-git-send-email-kwankhede@nvidia.com>
X-NVConfidentiality: public
MIME-Version: 1.0
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1589783319; bh=s4Iv0GJDj+1bhl4jbE8YcxRvsfl81dyjXBeOzB1RdI0=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         In-Reply-To:References:X-NVConfidentiality:MIME-Version:
         Content-Type;
        b=WizfX8YDczCr9Q66QkkPLpVqUOV9CVHtyv60PyhInuaVwSX6vsX3S2YazenjfJLe/
         6g/bxI75E1ryQb7C9XnIiXde3SKeWpjcW6nv2vYEc3vDZyW0OdFD/qnzxubF2AcI0z
         rajnYw2Tq+yJnen9U5Hn1uVnspuklH8c09r7nSElqtCX/l1zk7Lj1zlj3Fj8+vvyo6
         OoE9nOXlBnxgCEe9fx2ldQyJNNLTT+Bkm8uPGuMz6M795NXm004DzzoHKdoNHVJDob
         Oi/0Ob/bqf9DVXcF6Ybr9LWOhz1q0MIpJSNvN//OGlBWaxLbGEo0Yu/6j6HRLuaRgc
         4CgCw8PSCih1g==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

- Defined MIGRATION region type and sub-type.

- Defined vfio_device_migration_info structure which will be placed at the
  0th offset of migration region to get/set VFIO device related
  information. Defined members of structure and usage on read/write access.

- Defined device states and state transition details.

- Defined sequence to be followed while saving and resuming VFIO device.

Signed-off-by: Kirti Wankhede <kwankhede@nvidia.com>
Reviewed-by: Neo Jia <cjia@nvidia.com>
---
 include/uapi/linux/vfio.h | 228 ++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 228 insertions(+)

```
#### [PATCH v2 1/7] exec: Let address_space_read/write_cached() propagate MemTxResult
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <f4bug@amsat.org>
X-Patchwork-Id: 11555619
Return-Path: <SRS0=OZeJ=7A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6A4CD913
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 May 2020 15:53:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 51D87207D8
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 May 2020 15:53:15 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="kCSqrZiB"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728397AbgERPxN (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 18 May 2020 11:53:13 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:42538 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728267AbgERPxM (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 18 May 2020 11:53:12 -0400
Received: from mail-wm1-x341.google.com (mail-wm1-x341.google.com
 [IPv6:2a00:1450:4864:20::341])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 5103CC061A0C
        for <kvm@vger.kernel.org>; Mon, 18 May 2020 08:53:12 -0700 (PDT)
Received: by mail-wm1-x341.google.com with SMTP id n5so50210wmd.0
        for <kvm@vger.kernel.org>; Mon, 18 May 2020 08:53:12 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=WSFyr6f19aP4N4MMJJARifgNu7cVe5tnytMgFa4vhLY=;
        b=kCSqrZiBJYfTvK6U7vz3nNDXw8i72uTGkX8UjayRNSx1b87A6HZyN0RCp9RgEzIN0G
         qWNlCkhAfu32BYTwCLRdc01DpTLebfKGRZENxPGloToarBft+JLovARNHt3Zm5JpiOFb
         VAmXclSfNHTPsASzzd+5Vo/Ib/iqvhUsdfDPO8VIutjrO5t7FrU6hlXCXcT5h2jVueTR
         s/m9n5HsKERdFsQ7+K4XiY/S9K6T8aned4oF9+6DsGouHBcACygZhGM0HhzemufQ8c0m
         1SMjBI0ljkR3A+dajrtCahHCwr35VD8FFfX24g9to1COczOsGSx8MST9/AnK7B7azqah
         +gGw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :in-reply-to:references:mime-version:content-transfer-encoding;
        bh=WSFyr6f19aP4N4MMJJARifgNu7cVe5tnytMgFa4vhLY=;
        b=tYk4lgG4Qr1Xb35Ejkee4gxt9udn9IokIXVVtPZbQN1BNRIOeTGzEUQCqEWbGRYk4W
         j15LknqAciHIphqbGjXkcgWLbNwajxnbuQB7jMkcd193hgq21DEqMCwU0n/3hx5TDAAF
         SvGyLpcCNMwBx/LH6wTZ50gK0WEu3BpScKbym1wkTWXqw8IskHkj5sIvzUYKO5Cce+7Q
         MWOqGyfL9VA2eFh98ldsARTH5ngFjNs4l+zpI/xLqX2tLSBZbGv8DhzvBtYJWOFct1mH
         zrueKXPWz0f+QsWmp1SbYM3BY64Fi7UvJel7m9QbuRXZj9UKG1qHhCQDINhBqM90qHrV
         DVkQ==
X-Gm-Message-State: AOAM532RmqivNAQgAAtMIEPag/0fHnsu1pTrUXmheHE3Hta0XKHBcl7o
        y8r/BqwaMwQaWfn0Nmz5h7U=
X-Google-Smtp-Source: 
 ABdhPJwFmlOQ4JYI++JR9ixqC4zYUF4jca3lwFeihkNHUxT11OuH2+k/On4eJQV74FyKNuuQu/d9Dg==
X-Received: by 2002:a7b:cf15:: with SMTP id l21mr32568wmg.172.1589817191110;
        Mon, 18 May 2020 08:53:11 -0700 (PDT)
Received: from x1w.redhat.com (17.red-88-21-202.staticip.rima-tde.net.
 [88.21.202.17])
        by smtp.gmail.com with ESMTPSA id
 7sm17647462wra.50.2020.05.18.08.53.10
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 18 May 2020 08:53:10 -0700 (PDT)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>
To: qemu-devel@nongnu.org
Cc: Peter Maydell <peter.maydell@linaro.org>,
 Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org,
 qemu-arm@nongnu.org, Richard Henderson <rth@twiddle.net>, =?utf-8?q?Philipp?=
	=?utf-8?q?e_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>
Subject: [PATCH v2 1/7] exec: Let address_space_read/write_cached() propagate
 MemTxResult
Date: Mon, 18 May 2020 17:53:02 +0200
Message-Id: <20200518155308.15851-2-f4bug@amsat.org>
X-Mailer: git-send-email 2.21.3
In-Reply-To: <20200518155308.15851-1-f4bug@amsat.org>
References: <20200518155308.15851-1-f4bug@amsat.org>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Both address_space_read_cached_slow() and
address_space_write_cached_slow() return a MemTxResult type.
Do not discard it, return it to the caller.

Signed-off-by: Philippe Mathieu-Daudé <f4bug@amsat.org>
Reviewed-by: Peter Maydell <peter.maydell@linaro.org>
---
 include/exec/memory.h | 19 +++++++++++--------
 exec.c                | 16 ++++++++--------
 2 files changed, 19 insertions(+), 16 deletions(-)

```
#### [PATCH 1/2] KVMM: export needed symbols
##### From: Anastassios Nanos <ananos@nubificus.co.uk>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Anastassios Nanos <ananos@nubificus.co.uk>
X-Patchwork-Id: 11554905
Return-Path: <SRS0=OZeJ=7A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DD2B5138A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 May 2020 06:58:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C5A6320715
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 May 2020 06:58:57 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726847AbgERG6y (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 18 May 2020 02:58:54 -0400
Received: from mail-wm1-f67.google.com ([209.85.128.67]:36513 "EHLO
        mail-wm1-f67.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726395AbgERG6y (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 18 May 2020 02:58:54 -0400
Received: by mail-wm1-f67.google.com with SMTP id u188so8947127wmu.1;
        Sun, 17 May 2020 23:58:51 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:references
         :mime-version:content-disposition:in-reply-to:user-agent;
        bh=O7T+/EGumFSPzoOShum9m7oeL5f+uhtFZ57+Qat4aGY=;
        b=KAwiot6DUlPOw+prBFpBgY5yxp56hmsVIviMlteBOT3/01FLRCSjnqTupZ1/67G9gc
         MaEjANG2n3ZbNYwdoY4L2FCSZDDn8KogYTvVHB9gA/0fKx3R1ROw3gX+83NAo2PxBGKV
         NhwCjELC4AQm8h1sfBllH859KvaTyUzjybTxdhZXJMqsS1MMjA3DkA4fpYu+liw6kTgX
         y3eRaPeTha9NXJX+zsV1oZ+nUxziH2hWl2dcQ8LHqwVOoZOTZqOaNmly51bf5Llc8cU+
         xmCXSig4pwZd988Y/3+9/60A3Pj9mOdRTAWS9+GhZutIbJr1kmxBMpuwhHqMT5/DnO/1
         EJag==
X-Gm-Message-State: AOAM532Oay/yiKHjd4xFnHxmW9fR38xbd9uyoth8q8IYjjvM38etGcBT
        Ml8Xm/8vK1/h/jpFiO+5ysE=
X-Google-Smtp-Source: 
 ABdhPJziKeISVJeZjvh8zgBsBnkBAV8uaBCLMrL8C5IqWyVUZSxvDOo3NNfa5lAX30DJd3X9N42Eug==
X-Received: by 2002:a1c:2c0b:: with SMTP id s11mr14062813wms.97.1589785130035;
        Sun, 17 May 2020 23:58:50 -0700 (PDT)
Received: from bf.nubificus.co.uk ([2a02:587:b919:800:aaa1:59ff:fe09:f176])
        by smtp.gmail.com with ESMTPSA id
 c143sm13770779wmd.43.2020.05.17.23.58.49
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Sun, 17 May 2020 23:58:49 -0700 (PDT)
Date: Mon, 18 May 2020 09:58:48 +0300
From: Anastassios Nanos <ananos@nubificus.co.uk>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        linux-kernel@vger.kernel.org
Cc: Marc Zyngier <maz@kernel.org>, James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Catalin Marinas <catalin.marinas@arm.com>,
        Will Deacon <will@kernel.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org, "H. Peter Anvin" <hpa@zytor.com>
Subject: [PATCH 1/2] KVMM: export needed symbols
Message-ID: 
 <33dddce13cd34448620b95db80a28b7b0bb906ad.1589784221.git.ananos@nubificus.co.uk>
References: <cover.1589784221.git.ananos@nubificus.co.uk>
MIME-Version: 1.0
Content-Disposition: inline
In-Reply-To: <cover.1589784221.git.ananos@nubificus.co.uk>
User-Agent: Mutt/1.10.1 (2018-07-13)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Expose a set of KVM functions to the kernel, in order to be
able to spawn a VM instance without assistance from user-space.
To handle a guest instance, the system needs access to the following
functions:

    kvm_arch_vcpu_run_map_fp
    kvm_arch_vcpu_ioctl_get_regs
    kvm_arch_vcpu_ioctl_set_regs
    kvm_arm_get_reg
    kvm_arm_set_reg
    kvm_arch_vcpu_ioctl_get_sregs
    kvm_arch_vcpu_ioctl_set_sregs
    kvm_vcpu_preferred_target
    kvm_vcpu_ioctl_set_cpuid2
    kvm_vcpu_ioctl_get_cpuid2
    kvm_dev_ioctl_get_cpuid
    kvm_arch_vcpu_ioctl_run
    kvm_arch_vcpu_ioctl_get_regs
    kvm_arch_vcpu_ioctl_set_regs
    kvm_arch_vcpu_ioctl_get_sregs
    kvm_arch_vcpu_ioctl_set_sregs
    kvm_vcpu_initialized
    kvm_arch_vcpu_ioctl_run
    kvm_arch_vcpu_ioctl_vcpu_init
    kvm_coalesced_mmio_init
    kvm_create_vm
    kvm_destroy_vm
    kvm_vm_ioctl_set_memory_region
    kvm_vm_ioctl_create_vcpu

Signed-off-by: Anastassios Nanos <ananos@nubificus.co.uk>
Signed-off-by: Charalampos Mainas <cmainas@nubificus.co.uk>
Signed-off-by: Konstantinos Papazafeiropoulos <kostis@nubificus.co.uk>
Signed-off-by: Stratos Psomadakis <psomas@nubificus.co.uk>
---
 arch/arm64/include/asm/kvm_host.h |  6 ++++
 arch/arm64/kvm/fpsimd.c           |  6 ++++
 arch/arm64/kvm/guest.c            | 48 +++++++++++++++++++++++++++++++
 arch/x86/kvm/cpuid.c              | 25 ++++++++++++++++
 arch/x86/kvm/x86.c                | 31 ++++++++++++++++++++
 include/linux/kvm_host.h          | 24 ++++++++++++++++
 virt/kvm/arm/arm.c                | 18 ++++++++++++
 virt/kvm/coalesced_mmio.c         |  6 ++++
 virt/kvm/kvm_main.c               | 23 +++++++++++++++
 9 files changed, 187 insertions(+)

```
#### [PATCH  1/2] KVM: nVMX: Fix VMX preemption timer migrationFrom: Makarand Sonare <makarandsonare@google.com>
##### From: Makarand Sonare <makarandsonare@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Makarand Sonare <makarandsonare@google.com>
X-Patchwork-Id: 11556287
Return-Path: <SRS0=OZeJ=7A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8123E13B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 May 2020 20:16:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 62CE520674
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 May 2020 20:16:27 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="YSBbVtqD"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726615AbgERUQ0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 18 May 2020 16:16:26 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:55830 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726250AbgERUQ0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 18 May 2020 16:16:26 -0400
Received: from mail-qv1-xf4a.google.com (mail-qv1-xf4a.google.com
 [IPv6:2607:f8b0:4864:20::f4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 01D15C061A0C
        for <kvm@vger.kernel.org>; Mon, 18 May 2020 13:16:26 -0700 (PDT)
Received: by mail-qv1-xf4a.google.com with SMTP id x26so12184908qvd.20
        for <kvm@vger.kernel.org>; Mon, 18 May 2020 13:16:25 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=Pt1B2qixiL3CFJ5I+kupJRBbX6SkGOtelCxexxp51bc=;
        b=YSBbVtqDsJ5kICdvfFDajm99EJt9v1ka267tjRDnxpMHLkKK33Xj/l9/dAI1NEcqk9
         as3YL3x9Omz5YNNaPcC8R2w3+o3WEMdQpCKjaj4UC3LWLGd7ny54KEFwpy/ixut2uPRm
         cLkXoZ4g9y5ZrDaxpCZ8zA9GKTxMsOyoJkW+Wl1G7RftYU4avxk1ZE5lPARy4Z3Oyx72
         jDShW9tOXgCp57Va3aE8O/fqSSfDWoHWBJtskoBSR1DVayU3WppHb7y0pEgjJdkd24YZ
         MWsZV8kw5CUN5ljISvL0swCajnR9ZuyKNlLEZSdU2vQszGrEuG3B/8kyZt0luAFPFTn6
         /d8w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=Pt1B2qixiL3CFJ5I+kupJRBbX6SkGOtelCxexxp51bc=;
        b=fTiGJrZkq9V1pcxtkKHHIApFLL+9xfMaRFpS/AnHjVQxZmPX5UQrDkSecpQnTvfDYK
         1GEWNfai6L+VnhLvP32wdF3NEThQi7QBo92NVaA3NzT61eUJ2UffhmR9XRXAGU2ryyuW
         iatcwvnpi8ddUTEwvj1FPph2Z3CzbXYzu2MqcgbnqSwTzB8HzXTTDM0a9oICTdIWhKk8
         ZESSodVOU15JicJyay1dlP+09aN93Q2hkaQ6tdFQz2+fHjE6/lWD+q24QcLEtVnqjVHT
         asQukyxsIC3t2nVi0ZboN3fCJEF0BG9JjWjkQi7ZQlTNtjErfR/DdDG+VLC7sHkhyEye
         hOVA==
X-Gm-Message-State: AOAM531NsMG8eb0hyNCrHRi9RVxKbPyjTembfFeZ4YsNTdJtiIULSbq1
        mfSwUhFDQHaHCYaSBKYtwf+xp+fi/O5UBcHv3I7SGHM7YfJzDXRuiQt+VNzkfjeZ7Yy2oTvNa+G
        Tu7pY4v4AbBdAq+ASP+N6iCDy+kAzIwq5l0j5rCca/k6q/UsiQbd9Mt3dpvTcFHBOXdfkeAtUf9
        ZVF7k=
X-Google-Smtp-Source: 
 ABdhPJygBn4Sy/cZriuGiLK59aZx/0Sw+zibaSUfNd/f9A+hJIp3jZ9UrzUEJjYO7TC4qhGOwQbvb2dsiuDqoXW/+nknEA==
X-Received: by 2002:a25:aaf2:: with SMTP id
 t105mr27490755ybi.26.1589832985025;
 Mon, 18 May 2020 13:16:25 -0700 (PDT)
Date: Mon, 18 May 2020 13:15:59 -0700
In-Reply-To: <20200518201600.255669-1-makarandsonare@google.com>
Message-Id: <20200518201600.255669-2-makarandsonare@google.com>
Mime-Version: 1.0
References: <20200518201600.255669-1-makarandsonare@google.com>
X-Mailer: git-send-email 2.26.2.761.g0e0b3e54be-goog
Subject: [PATCH  1/2] KVM: nVMX: Fix VMX preemption timer migration
From: Makarand Sonare <makarandsonare@google.com>
To: kvm@vger.kernel.org, pshier@google.com, jmattson@google.com
Cc: Makarand Sonare <makarandsonare@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Peter Shier <pshier@google.com>

Add new field to hold preemption timer expiration deadline
appended to struct kvm_vmx_nested_state_data. This is to prevent
the first VM-Enter after migration from incorrectly restarting the timer
with the full timer value instead of partially decayed timer value.
KVM_SET_NESTED_STATE restarts timer using migrated state regardless
of whether L1 sets VM_EXIT_SAVE_VMX_PREEMPTION_TIMER.

Fixes: cf8b84f48a593 ("kvm: nVMX: Prepare for checkpointing L2 state")

Signed-off-by: Peter Shier <pshier@google.com>
Signed-off-by: Makarand Sonare <makarandsonare@google.com>
Change-Id: I6446aba5a547afa667f0ef4620b1b76115bf3753
---
 Documentation/virt/kvm/api.rst        |  4 ++
 arch/x86/include/uapi/asm/kvm.h       |  2 +
 arch/x86/kvm/vmx/nested.c             | 61 ++++++++++++++++++++++++---
 arch/x86/kvm/vmx/vmx.h                |  1 +
 arch/x86/kvm/x86.c                    |  3 +-
 include/uapi/linux/kvm.h              |  1 +
 tools/arch/x86/include/uapi/asm/kvm.h |  2 +
 7 files changed, 67 insertions(+), 7 deletions(-)

```
#### [RFC PATCH v4 01/10] vfio/pci: register/unregister vfio_pci_vendor_driver_ops
##### From: Yan Zhao <yan.y.zhao@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yan Zhao <yan.y.zhao@intel.com>
X-Patchwork-Id: 11554619
Return-Path: <SRS0=OZeJ=7A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B0B9360D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 May 2020 02:53:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9DA12207F9
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 May 2020 02:53:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726726AbgERCxn (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 17 May 2020 22:53:43 -0400
Received: from mga06.intel.com ([134.134.136.31]:38912 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726675AbgERCxn (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 17 May 2020 22:53:43 -0400
IronPort-SDR: 
 v0031KGH8sPzZNW36l48JiqLD/Ypcles9iwOm9NYyPTbJvPwu16AgLt8YEuwUX9YhZBGwVDpLz
 hI4jkWd3plUw==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 17 May 2020 19:53:42 -0700
IronPort-SDR: 
 ajl1mKmNYUq8JZW6h0P0xcT210nfq6Cn+lB1ky8e0KlSTGHH5i3gnWv1CM7K3UqhXBHZhDBz1b
 Aw4BnjPfMmdg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,405,1583222400";
   d="scan'208";a="411103805"
Received: from joy-optiplex-7040.sh.intel.com ([10.239.13.16])
  by orsmga004.jf.intel.com with ESMTP; 17 May 2020 19:53:39 -0700
From: Yan Zhao <yan.y.zhao@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: alex.williamson@redhat.com, cohuck@redhat.com,
        zhenyuw@linux.intel.com, zhi.a.wang@intel.com,
        kevin.tian@intel.com, shaopeng.he@intel.com, yi.l.liu@intel.com,
        xin.zeng@intel.com, hang.yuan@intel.com,
        Yan Zhao <yan.y.zhao@intel.com>
Subject: [RFC PATCH v4 01/10] vfio/pci: register/unregister
 vfio_pci_vendor_driver_ops
Date: Sun, 17 May 2020 22:43:17 -0400
Message-Id: <20200518024317.14055-1-yan.y.zhao@intel.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200518024202.13996-1-yan.y.zhao@intel.com>
References: <20200518024202.13996-1-yan.y.zhao@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

vfio_pci_vendor_driver_ops includes two parts:
(1) .probe() and .remove() interface to be called by vfio_pci_probe()
and vfio_pci_remove().
(2) pointer to struct vfio_device_ops. It will be registered as ops of vfio
device if .probe() succeeds.

Suggested-by: Alex Williamson <alex.williamson@redhat.com>
Signed-off-by: Yan Zhao <yan.y.zhao@intel.com>
---
 drivers/vfio/pci/vfio_pci.c         | 102 +++++++++++++++++++++++++++-
 drivers/vfio/pci/vfio_pci_private.h |   7 ++
 include/linux/vfio.h                |   9 +++
 3 files changed, 117 insertions(+), 1 deletion(-)

```
#### [PATCH] KVM: Fix the indentation to match coding style
##### From: Haiwei Li <lihaiwei.kernel@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Haiwei Li <lihaiwei.kernel@gmail.com>
X-Patchwork-Id: 11554543
Return-Path: <SRS0=OZeJ=7A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5024290
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 May 2020 01:31:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2B12020820
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 May 2020 01:31:54 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="C1uMgafZ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726722AbgERBbv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 17 May 2020 21:31:51 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:49384 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726675AbgERBbu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 17 May 2020 21:31:50 -0400
Received: from mail-pj1-x1044.google.com (mail-pj1-x1044.google.com
 [IPv6:2607:f8b0:4864:20::1044])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id BE165C061A0C;
        Sun, 17 May 2020 18:31:50 -0700 (PDT)
Received: by mail-pj1-x1044.google.com with SMTP id z15so5911575pjb.0;
        Sun, 17 May 2020 18:31:50 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=to:cc:from:subject:message-id:date:user-agent:mime-version
         :content-language:content-transfer-encoding;
        bh=XbbeOrIKm/c92sezKdJ+YKW0B19HCAv4ShgmKI4t9O0=;
        b=C1uMgafZPLI1CmiPPlSGD+j1w/O21KhGp/nVMAUmZZahlntQ5AImgRwjcMimEWKMZd
         u0EX2GnlBDgoRTg2L94uXyc3ec9ZUSvy/BUeUdOuINT7VY4X33OkOMLv6we0KszbVwg9
         PBB+o/r2xNf7uWDkIKU+qz6yFUDScF2RXb+J4sYVvf0In5utQbm9hCyBvdMVGlyu6rUL
         z1TY7JqZ47uWoq/edbQNoG/Zj2N5vi4nOEEI27V9ZtV2Y2223zCl0kEQXVoGl8dfT38S
         z2GJ93Ct6slq2RHWDIlxEOohkDR+OHzgP87JCT2MTrwixW1s/GDK87tGt58c6VbWLcLM
         AZPA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:to:cc:from:subject:message-id:date:user-agent
         :mime-version:content-language:content-transfer-encoding;
        bh=XbbeOrIKm/c92sezKdJ+YKW0B19HCAv4ShgmKI4t9O0=;
        b=sFveExF/rm3ntVxYD9//pVlAorxShfGnnFT4seA2EtCVC2vmpUf7WdYydyTR+h4DBe
         tDl4NqjGDVjpUCg802KdXIoF/7jv2tnJHOiiPNqOLDmoh2++tW57XqGQXXAvKeZfWz0k
         fn8QMEoC5t24YbBSIxNRshTsc9mVr7BUdHG8/5FTgrKgTIKFBwHuwNLFDX5YtrcufmDG
         IKVaf7XSMtzTDzann/f07Gmhcrn/GMsVSsVjPZrH/l2leOAG98M/pgYT/rKJpJndAMm5
         7iWovl05yPX4a5ydMrin+jPUdf04SHdBg6/0fgLM2gZLU9mcOf4vsp2h1IZQtR2FS+S/
         LZ6g==
X-Gm-Message-State: AOAM5307WYauFfn1bvyXknB2wcqtItb0+/brmc3WPW5cnIpTUbScrBAh
        CcgMTWhL/h8Ma9vDQVGVuQ==
X-Google-Smtp-Source: 
 ABdhPJylnx5A4YEXQxyR3b8JnxFKlIooqc0aPcvyT8oydsJLmZID07Pk9PloLJVNByonA1GpFLRvfA==
X-Received: by 2002:a17:902:32b:: with SMTP id
 40mr13783259pld.73.1589765510189;
        Sun, 17 May 2020 18:31:50 -0700 (PDT)
Received: from [127.0.0.1] ([103.7.29.7])
        by smtp.gmail.com with ESMTPSA id
 h9sm7121572pfo.129.2020.05.17.18.31.46
        (version=TLS1_3 cipher=TLS_AES_128_GCM_SHA256 bits=128/128);
        Sun, 17 May 2020 18:31:49 -0700 (PDT)
To: "pbonzini@redhat.com" <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        "vkuznets@redhat.com" <vkuznets@redhat.com>, wanpengli@tencent.com,
        "jmattson@google.com" <jmattson@google.com>,
        "joro@8bytes.org" <joro@8bytes.org>,
        "tglx@linutronix.de" <tglx@linutronix.de>,
        "mingo@redhat.com" <mingo@redhat.com>,
        "bp@alien8.de" <bp@alien8.de>, hpa@zytor.com
Cc: "x86@kernel.org" <x86@kernel.org>, kvm@vger.kernel.org,
        "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>
From: Haiwei Li <lihaiwei.kernel@gmail.com>
Subject: [PATCH] KVM: Fix the indentation to match coding style
Message-ID: <2f78457e-f3a7-3bc9-e237-3132ee87f71e@gmail.com>
Date: Mon, 18 May 2020 09:31:38 +0800
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:68.0)
 Gecko/20100101 Thunderbird/68.8.0
MIME-Version: 1.0
Content-Language: en-US
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Haiwei Li <lihaiwei@tencent.com>

There is a bad indentation in next&queue branch. The patch looks like 
fixes nothing though it fixes the indentation.

Before fixing:

                 if (!handle_fastpath_set_x2apic_icr_irqoff(vcpu, data)) {
                         kvm_skip_emulated_instruction(vcpu);
                         ret = EXIT_FASTPATH_EXIT_HANDLED;
                }
                 break;
         case MSR_IA32_TSCDEADLINE:

After fixing:

                 if (!handle_fastpath_set_x2apic_icr_irqoff(vcpu, data)) {
                         kvm_skip_emulated_instruction(vcpu);
                         ret = EXIT_FASTPATH_EXIT_HANDLED;
                 }
                 break;
         case MSR_IA32_TSCDEADLINE:


Signed-off-by: Haiwei Li <lihaiwei@tencent.com>
Reviewed-by: Wanpeng Li <wanpengli@tencent.com>
---
  arch/x86/kvm/x86.c | 2 +-
  1 file changed, 1 insertion(+), 1 deletion(-)

                 data = kvm_read_edx_eax(vcpu);
--
1.8.3.1

```
#### [PATCH kvmtool v2] net: uip: Fix GCC 10 warning about checksum calculation
##### From: Andre Przywara <andre.przywara@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: =?utf-8?q?Andr=C3=A9_Przywara?=
 <andre.przywara@arm.com>
X-Patchwork-Id: 11555403
Return-Path: <SRS0=OZeJ=7A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 73C6A138A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 May 2020 12:56:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 58DAC20787
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 May 2020 12:56:57 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726940AbgERM44 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 18 May 2020 08:56:56 -0400
Received: from foss.arm.com ([217.140.110.172]:39934 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726709AbgERM44 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 18 May 2020 08:56:56 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 3985E101E;
        Mon, 18 May 2020 05:56:55 -0700 (PDT)
Received: from donnerap.arm.com (donnerap.cambridge.arm.com [10.1.197.25])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 676FB3F305;
        Mon, 18 May 2020 05:56:54 -0700 (PDT)
From: Andre Przywara <andre.przywara@arm.com>
To: Will Deacon <will@kernel.org>,
        Julien Thierry <julien.thierry.kdev@gmail.com>
Cc: Alexandru Elisei <alexandru.elisei@arm.com>, kvm@vger.kernel.org
Subject: [PATCH kvmtool v2] net: uip: Fix GCC 10 warning about checksum
 calculation
Date: Mon, 18 May 2020 13:56:49 +0100
Message-Id: <20200518125649.216416-1-andre.przywara@arm.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

GCC 10.1 generates a warning in net/ip/csum.c about exceeding a buffer
limit in a memcpy operation:
------------------
In function 'memcpy',
    inlined from 'uip_csum_udp' at net/uip/csum.c:58:3:
/usr/include/aarch64-linux-gnu/bits/string_fortified.h:34:10: error: writing 1 byte into a region of size 0 [-Werror=stringop-overflow=]
   34 |   return __builtin___memcpy_chk (__dest, __src, __len, __bos0 (__dest));
      |          ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
In file included from net/uip/csum.c:1:
net/uip/csum.c: In function 'uip_csum_udp':
include/kvm/uip.h:132:6: note: at offset 0 to object 'sport' with size 2 declared here
  132 |  u16 sport;
------------------

This warning originates from the code taking the address of the "sport"
member, then using that with some pointer arithmetic in a memcpy call.
GCC now sees that the object is only a u16, so copying 12 bytes into it
cannot be any good.
It's somewhat debatable whether this is a legitimate warning, as there
is enough storage at that place, and we knowingly use the struct and
its variabled-sized member at the end.

However we can also rewrite the code, to not abuse the "&" operation of
some *member*, but take the address of the struct itself.
This makes the code less dodgy, and indeed appeases GCC 10.

Signed-off-by: Andre Przywara <andre.przywara@arm.com>
Reported-by: Alexandru Elisei <alexandru.elisei@arm.com>
Reviewed-by: Alexandru Elisei <alexandru.elisei@arm.com>
Tested-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
Changes v1 ... v2:
- add tags
- remove Unicode from commit message
- add space between type and pointer

 net/uip/csum.c | 26 ++++++++++++--------------
 1 file changed, 12 insertions(+), 14 deletions(-)

```
#### [PATCH] KVM: x86: respect singlestep when emulating instruction
##### From: Felipe Franciosi <felipe@nutanix.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Felipe Franciosi <felipe@nutanix.com>
X-Patchwork-Id: 11556427
Return-Path: <SRS0=OZeJ=7A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BE993912
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 May 2020 21:41:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A68E720835
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 May 2020 21:41:34 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=sendgrid.net header.i=@sendgrid.net
 header.b="K36rKQEh"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728115AbgERVld (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 18 May 2020 17:41:33 -0400
Received: from o1.dev.nutanix.com ([198.21.4.205]:46847 "EHLO
        o1.dev.nutanix.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726492AbgERVld (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 18 May 2020 17:41:33 -0400
X-Greylist: delayed 301 seconds by postgrey-1.27 at vger.kernel.org;
 Mon, 18 May 2020 17:41:33 EDT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=sendgrid.net;
        h=from:to:cc:subject:mime-version:content-transfer-encoding;
        s=smtpapi; bh=JyhxMm+Y9a7fjPz/PBMgYlMCWgvafYN43d9h18/IJbI=; b=K3
        6rKQEhR78CJvDghmo3MHIE6s5bH5bs5zAp8nvnnkhgve+Kdbd9XDenKd1LfjSPqe
        f0o1wsVQDVbFasd6HPA7jqxEoAXTglsrpRQ13/CDKEy0KD6RV9tSzgqxDv3Sg15W
        xQeeBpDWXG4icd4d5GZ1ggwZ2/QylNf3u084ELG1Q=
Received: by filter1137p1las1.sendgrid.net with SMTP id
 filter1137p1las1-22580-5EC2FFE0-18
        2020-05-18 21:36:32.413492831 +0000 UTC m=+8938.670754625
Received: from debian.localdomain (unknown)
        by ismtpd0005p1lon1.sendgrid.net (SG) with ESMTP id
 GjyWYWl9Q9OZMewhNqAgqw
        Mon, 18 May 2020 21:36:31.830 +0000 (UTC)
From: Felipe Franciosi <felipe@nutanix.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org, stable@vger.kernel.org,
        Felipe Franciosi <felipe@nutanix.com>
Subject: [PATCH] KVM: x86: respect singlestep when emulating instruction
Date: Mon, 18 May 2020 21:36:32 +0000 (UTC)
Message-Id: <20200518213620.2216-1-felipe@nutanix.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
content-transfer-encoding: quoted-printable
X-SG-EID: 
 lJkaZ7x5+v8tEWA8V7PwHOTpzaP4FLDpHSpMO5CvnfS3TcNsgO+IWDMtZpC31rA+Ml4lqauBq7PuO0
 Tp/Sco3DrKv08EaUP2dfu4ZD2CRPZ3dcX1C6abQgMQb6rsrIFAbXBsa4BeGOgFPLwkeHBQZNLKuHRF
 XrxFL6AyKqqeV4xOuMUwvikEMsGSQI2QRmThgFEPRFistpid0VXh/ykGNUDhWfq5JoHCkySmYBNJ6G
 c=
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When userspace configures KVM_GUESTDBG_SINGLESTEP, KVM will manage the
presence of X86_EFLAGS_TF via kvm_set/get_rflags on vcpus. The actual
rflag bit is therefore hidden from callers.

That includes init_emulate_ctxt() which uses the value returned from
kvm_get_flags() to set ctxt->tf. As a result, x86_emulate_instruction()
will skip a single step, leaving singlestep_rip stale and not returning
to userspace.

This resolves the issue by observing the vcpu guest_debug configuration
alongside ctxt->tf in x86_emulate_instruction(), performing the single
step if set.

Signed-off-by: Felipe Franciosi <felipe@nutanix.com>
---
 arch/x86/kvm/x86.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [QEMU RFC PATCH v4] hw/vfio/pci: remap bar region irq
##### From: Yan Zhao <yan.y.zhao@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yan Zhao <yan.y.zhao@intel.com>
X-Patchwork-Id: 11554643
Return-Path: <SRS0=OZeJ=7A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D5C4C13B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 May 2020 03:06:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B853520826
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 May 2020 03:06:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726944AbgERDG0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 17 May 2020 23:06:26 -0400
Received: from mga06.intel.com ([134.134.136.31]:39772 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726639AbgERDG0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 17 May 2020 23:06:26 -0400
IronPort-SDR: 
 bXB6AeMxhvwiK9dC5jY/JRLc3Z7xfq/fIcezBTm/K6dEsDpF9gr7VFae/p7Zp/loP/vNg3tBjc
 qpIEnAHcmFaw==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 17 May 2020 20:06:26 -0700
IronPort-SDR: 
 ZodtljUh9+7MSzGOSifcMary7mu0dRa+dQOFzSBH2T0ZlWSnK8HGJjF9JydYxVA7Q3evPo+gpa
 +Opeg/vPxmkQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,405,1583222400";
   d="scan'208";a="411106816"
Received: from joy-optiplex-7040.sh.intel.com ([10.239.13.16])
  by orsmga004.jf.intel.com with ESMTP; 17 May 2020 20:06:22 -0700
From: Yan Zhao <yan.y.zhao@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: alex.williamson@redhat.com, cohuck@redhat.com,
        zhenyuw@linux.intel.com, zhi.a.wang@intel.com,
        kevin.tian@intel.com, shaopeng.he@intel.com, yi.l.liu@intel.com,
        xin.zeng@intel.com, hang.yuan@intel.com,
        Yan Zhao <yan.y.zhao@intel.com>
Subject: [QEMU RFC PATCH v4] hw/vfio/pci: remap bar region irq
Date: Sun, 17 May 2020 22:56:18 -0400
Message-Id: <20200518025618.14659-1-yan.y.zhao@intel.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200518025245.14425-1-yan.y.zhao@intel.com>
References: <20200518025245.14425-1-yan.y.zhao@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Added an irq type VFIO_IRQ_TYPE_REMAP_BAR_REGION to
dynamically query and remap BAR regions.

QEMU decodes the index of the BARs by reading cnt of eventfd.
If bit n is set, the corresponding BAR will be requeried and
its subregions will be remapped according to the its new flags.

rely on [1] "vfio: Add a funtion to return a specific irq capabilities"
[1] https://www.mail-archive.com/qemu-devel@nongnu.org/msg621645.html

Signed-off-by: Yan Zhao <yan.y.zhao@intel.com>
---
 hw/vfio/common.c              | 50 ++++++++++++++++++++++++
 hw/vfio/pci.c                 | 90 +++++++++++++++++++++++++++++++++++++++++++
 hw/vfio/pci.h                 |  2 +
 include/hw/vfio/vfio-common.h |  2 +
 linux-headers/linux/vfio.h    | 11 ++++++
 5 files changed, 155 insertions(+)

```
#### [kvm-unit-tests PATCH v7 01/12] s390x: saving regs for interrupts
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11555659
Return-Path: <SRS0=OZeJ=7A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5B2C6912
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 May 2020 16:07:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4E91C207ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 May 2020 16:07:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728326AbgERQHm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 18 May 2020 12:07:42 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:18816 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728286AbgERQHk (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 18 May 2020 12:07:40 -0400
Received: from pps.filterd (m0187473.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 04IG2Jsx113630;
        Mon, 18 May 2020 12:07:40 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 312btuaueb-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 18 May 2020 12:07:40 -0400
Received: from m0187473.ppops.net (m0187473.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 04IG2Npx113874;
        Mon, 18 May 2020 12:07:39 -0400
Received: from ppma05fra.de.ibm.com (6c.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.108])
        by mx0a-001b2d01.pphosted.com with ESMTP id 312btuauct-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 18 May 2020 12:07:39 -0400
Received: from pps.filterd (ppma05fra.de.ibm.com [127.0.0.1])
        by ppma05fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 04IG6n7b002160;
        Mon, 18 May 2020 16:07:36 GMT
Received: from b06avi18878370.portsmouth.uk.ibm.com
 (b06avi18878370.portsmouth.uk.ibm.com [9.149.26.194])
        by ppma05fra.de.ibm.com with ESMTP id 313wf1g0cf-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 18 May 2020 16:07:35 +0000
Received: from d06av25.portsmouth.uk.ibm.com (d06av25.portsmouth.uk.ibm.com
 [9.149.105.61])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 04IG7X1Z9372150
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 18 May 2020 16:07:33 GMT
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 5663B11C04C;
        Mon, 18 May 2020 16:07:33 +0000 (GMT)
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 023DA11C052;
        Mon, 18 May 2020 16:07:33 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.158.244])
        by d06av25.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon, 18 May 2020 16:07:32 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, frankja@linux.ibm.com,
        david@redhat.com, thuth@redhat.com, cohuck@redhat.com
Subject: [kvm-unit-tests PATCH v7 01/12] s390x: saving regs for interrupts
Date: Mon, 18 May 2020 18:07:20 +0200
Message-Id: <1589818051-20549-2-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1589818051-20549-1-git-send-email-pmorel@linux.ibm.com>
References: <1589818051-20549-1-git-send-email-pmorel@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.216,18.0.676
 definitions=2020-05-18_06:2020-05-15,2020-05-18 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 suspectscore=1 bulkscore=0
 priorityscore=1501 malwarescore=0 mlxscore=0 mlxlogscore=975
 impostorscore=0 spamscore=0 clxscore=1015 cotscore=-2147483648
 lowpriorityscore=0 adultscore=0 phishscore=0 classifier=spam adjust=0
 reason=mlx scancount=1 engine=8.12.0-2004280000
 definitions=main-2005180134
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If we use multiple source of interrupts, for example, using SCLP
console to print information while using I/O interrupts, we need
to have a re-entrant register saving interruption handling.

Instead of saving at a static memory address, let's save the base
registers, the floating point registers and the floating point
control register on the stack in case of I/O interrupts

Note that we keep the static register saving to recover from the
RESET tests.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
---
 s390x/cstart64.S | 41 +++++++++++++++++++++++++++++++++++++++--
 1 file changed, 39 insertions(+), 2 deletions(-)

```
