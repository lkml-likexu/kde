#### [PATCH 1/4] kvm: x86: add KVM_{GET,SET}_TSC_OFFSET ioctlsFrom: Oliver Upton <oupton@google.com>
##### From: Oliver Upton <oupton@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Oliver Upton <oupton@google.com>
X-Patchwork-Id: 11657355
Return-Path: <SRS0=WjKu=AV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2E3B86C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jul 2020 20:07:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 14CA12076A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jul 2020 20:07:50 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="O3+mbm6u"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727866AbgGJUHs (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 10 Jul 2020 16:07:48 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:39712 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726867AbgGJUHr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 10 Jul 2020 16:07:47 -0400
Received: from mail-pj1-x1049.google.com (mail-pj1-x1049.google.com
 [IPv6:2607:f8b0:4864:20::1049])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 550C4C08C5DC
        for <kvm@vger.kernel.org>; Fri, 10 Jul 2020 13:07:47 -0700 (PDT)
Received: by mail-pj1-x1049.google.com with SMTP id t12so4686402pju.8
        for <kvm@vger.kernel.org>; Fri, 10 Jul 2020 13:07:47 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=J0bTU87L8QsjBDphnGPI3tqvqXPCIpODhyPeANR5PoI=;
        b=O3+mbm6uPCewPDwc6fCuyXjfnu86dQsncgWA+tpANzL6Lb/vCRG54HYxwCBWfomQAK
         gNNOe3fPNGin42JlGpisTBcxr54nh/8U8SqW3dA+J1AvzrMVr9bhHr+bpUS6Cg39iVkn
         0OmgAxnYHRXbG8wbWhgcyUBnGGnXMzqmW2WgGQv4LEeHTIGQuKSF6frcNIij5PYxfeqb
         vyqBV2Ealq95VRPNRSzENmLpM1WDfdewN+PaAjLaoP5OKVqUVWgIOeFcid51UZ92rooc
         /wxakK3UKLymkpeqn75XLJzeKG2hWU97Jd1Vk57RvdH+tbfkaSHuSznX7vbnp/994V0s
         2aHQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=J0bTU87L8QsjBDphnGPI3tqvqXPCIpODhyPeANR5PoI=;
        b=bNPqN5sX7LwY7AqtExIPRDk0ogV46hX4UeEo0MN6WVhEkxz4nVbHlE9wE32EoKEHyz
         EqmzB5bJF7Dw1BJYB4EbkDBB+Nexfi/pZu2fP9YqLprR3tXgbgUe2WmmdBQ4v6QyIDxJ
         ErKHzUh337dyse2dSiL0yhL2csooqEcsuplA3IykeAIm6JKP3DkzT4U6VmBpNNk77Bi9
         UHZ0/l/DcVrFTrCtBirAmOPvAK87DHc2KGBTGxdz/mVRpCjLyIFLmj+dRTzZntWXN+uB
         mu1VJYOrbX4bbeT8toK37WzRtSuMOpA6nocQAzsa2fmIHFrxtYIO2DQgYiN2e0+XHusI
         VXRw==
X-Gm-Message-State: AOAM532STi9ysZ0pX0ivgLyZ/Ccd/XgjqHKLSKnpi/KmZTwVdKbHvLtR
        1nwk+AtnDfOdZ6d+O+kxT+Q2j3lg99OOdvu+yQ9tT4IjRygOtwGj3pSdCUd/IXwyXgUoExNBGYr
        SGj3zm2aNR3cvZeY3YU+qlTW1IaFjnpuiKoZ9Tag4B/vNlvM53kEbzInF9Q==
X-Google-Smtp-Source: 
 ABdhPJwgzBxRsj6W9Kn2DNPB0HOMGjTt45tmjSdTBguSsiq5XDLFTTFXQK2p/8lQngo/XR+hnkkRVwG6raI=
X-Received: by 2002:aa7:934a:: with SMTP id 10mr27356132pfn.302.1594411666413;
 Fri, 10 Jul 2020 13:07:46 -0700 (PDT)
Date: Fri, 10 Jul 2020 20:07:40 +0000
Message-Id: <20200710200743.3992127-1-oupton@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.27.0.383.g050319c2ae-goog
Subject: [PATCH 1/4] kvm: x86: add KVM_{GET,SET}_TSC_OFFSET ioctls
From: Oliver Upton <oupton@google.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Peter Shier <pshier@google.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Peter Hornyack <peterhornyack@google.com>,
        Jim Mattson <jmattson@google.com>,
        Oliver Upton <oupton@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Peter Hornyack <peterhornyack@google.com>

The KVM_SET_MSR vcpu ioctl has some temporal and value-based heuristics
for determining when userspace is attempting to synchronize TSCs.
Instead of guessing at userspace's intentions in the kernel, directly
expose control of the TSC offset field to userspace such that userspace
may deliberately synchronize the guest TSCs.

Note that TSC offset support is mandatory for KVM on both SVM and VMX.

Reviewed-by: Jim Mattson <jmattson@google.com>
Signed-off-by: Peter Hornyack <peterhornyack@google.com>
Signed-off-by: Oliver Upton <oupton@google.com>
---
 Documentation/virt/kvm/api.rst | 27 +++++++++++++++++++++++++++
 arch/x86/kvm/x86.c             | 28 ++++++++++++++++++++++++++++
 include/uapi/linux/kvm.h       |  5 +++++
 3 files changed, 60 insertions(+)

```
#### [GIT PULL] Second batch of KVM changes for Linux 5.8-rc5
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11656545
Return-Path: <SRS0=WjKu=AV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 952CD13B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jul 2020 13:07:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 775492078B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jul 2020 13:07:09 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="OXqrH9wg"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727865AbgGJNHF (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 10 Jul 2020 09:07:05 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:47897 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727046AbgGJNHE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 10 Jul 2020 09:07:04 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1594386423;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=IrQ2y6oqMFzcLSC+a+hsU9IW+yAmZRwX9zeWYh8Q/Zs=;
        b=OXqrH9wgjUlSoD44ewjpXRKRekdoaEgeLzQc2eKLARQte/uxv1MYLA3tyMNoFtAQUSy0bp
        uzDi+qkp/oJOpQL2Tf2dOyVqLfYIT9OQ4Q5jRBK8WunodQ4ADbwathuK8L0DPhvomDvOLv
        GMplmINDvmklw/GCA76q7BbPXyV/MN0=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-40-3v4nffOSP_-9xvqzVJ-YQw-1; Fri, 10 Jul 2020 09:07:01 -0400
X-MC-Unique: 3v4nffOSP_-9xvqzVJ-YQw-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 8B21C100960F;
        Fri, 10 Jul 2020 13:07:00 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 2878D724A4;
        Fri, 10 Jul 2020 13:07:00 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: torvalds@linux-foundation.org
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [GIT PULL] Second batch of KVM changes for Linux 5.8-rc5
Date: Fri, 10 Jul 2020 09:06:59 -0400
Message-Id: <20200710130659.10507-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linus,

The following changes since commit 8038a922cf9af5266eaff29ce996a0d1b788fc0d:

  Merge tag 'kvmarm-fixes-5.8-3' of git://git.kernel.org/pub/scm/linux/kernel/git/kvmarm/kvmarm into kvm-master (2020-07-06 13:05:38 -0400)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to 3d9fdc252b52023260de1d12399cb3157ed28c07:

  KVM: MIPS: Fix build errors for 32bit kernel (2020-07-10 06:15:38 -0400)

----------------------------------------------------------------
Two simple but important bugfixes.

----------------------------------------------------------------
Huacai Chen (1):
      KVM: MIPS: Fix build errors for 32bit kernel

Paolo Bonzini (1):
      KVM: nVMX: fixes for preemption timer migration

 Documentation/virt/kvm/api.rst  | 5 +++--
 arch/mips/kvm/emulate.c         | 4 ++++
 arch/x86/include/uapi/asm/kvm.h | 5 +++--
 arch/x86/kvm/vmx/nested.c       | 1 +
 4 files changed, 11 insertions(+), 4 deletions(-)
```
#### [PATCH] KVM: MIPS: Fix build errors for 32bit kernel
##### From: Huacai Chen <chenhc@lemote.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Huacai Chen <chenhc@lemote.com>
X-Patchwork-Id: 11655837
Return-Path: <SRS0=WjKu=AV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A285514F6
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jul 2020 07:21:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 883E42078D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jul 2020 07:21:17 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="Cdth6s5B"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727061AbgGJHVR (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 10 Jul 2020 03:21:17 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:34066 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725966AbgGJHVQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 10 Jul 2020 03:21:16 -0400
Received: from mail-pl1-x642.google.com (mail-pl1-x642.google.com
 [IPv6:2607:f8b0:4864:20::642])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 8DFF5C08C5CE;
        Fri, 10 Jul 2020 00:21:16 -0700 (PDT)
Received: by mail-pl1-x642.google.com with SMTP id q17so1883287pls.9;
        Fri, 10 Jul 2020 00:21:16 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=lKn1gJPWAF3xCGoJfzCQprGwxZKYhV13Di2vFMkiPwU=;
        b=Cdth6s5BDzvWIcTFQtl1GiJab7NvY2MWI7cSZO0DzMZZI6Yso3NDBEdHJO1UBJN6sW
         YWk7trE3R0c4U4T+zkGiQoubhS5G6YpoghznjD0MDyijU57SLEZCPeqDPWZojicFQdzF
         bgXEC5Qv45JDSSY/3ofqMZlHi51pYTxJuiF2WNGX5J+stKKwQ97WS1YGlOWsQYUj/h6K
         dHJBCq0OVztahA8gtmzXT1/aSjK7SI5qhE2hBJJXeAANwL18SsJAs+5H8xv3HsWEf+U5
         sSW0ZEZ41iQeCGRDGCNpzXCC72fBqbm5ovuacRFDqyykH8bzxo5sLdGIiTUHEM+3JIZn
         ZwYA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=lKn1gJPWAF3xCGoJfzCQprGwxZKYhV13Di2vFMkiPwU=;
        b=bBojgyZNkLAT41t36mk86Ja/Vv4YAQgCDR1svJUVfYMOfHGIVr6ZAdFrEJ/gpCBU7p
         LB1kh5BqOP81wqn21icUF8KZo4kjFAhDITZbC45mHeaHM3XFWBqGg6zqu7b+M9N0Fy7F
         UZxFZ6x0f8jTBdPNVhWmMY3k3aH32ZXoe3eNNtsC+W5WC1cQDaoK2K3t+5i3RWL2TeuW
         V+G6b+ofHqArImrXsc+mRyy4Sr62R1gCxuKzijd03EPtMe/ma2InmxHZ+InEZH7QK/Xo
         5PCCm15tNGwXypi9ZKYn4YxoYErLqujg+YdxN3Wl/RclaO4jmCv3ILUlRZihvqD1obqN
         ypAA==
X-Gm-Message-State: AOAM533UC1m/OknBBIeaCVqGlth1P5SulDqAm6RK3wSQD6XVQZ2jGSap
        8bHaJAe+pXtxVqeAeh9SAlC2HLBc1jj1xg==
X-Google-Smtp-Source: 
 ABdhPJxT8JqIehWkOMptuYE0fjcRDwBcxZZEW2ZhyEExBpOeSwALsjELvi4Z7Vf+1yq9vjK9WpNAxQ==
X-Received: by 2002:a17:902:b705:: with SMTP id
 d5mr47019814pls.118.1594365676112;
        Fri, 10 Jul 2020 00:21:16 -0700 (PDT)
Received: from software.domain.org (28.144.92.34.bc.googleusercontent.com.
 [34.92.144.28])
        by smtp.gmail.com with ESMTPSA id
 q10sm5411635pfk.86.2020.07.10.00.21.12
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Fri, 10 Jul 2020 00:21:15 -0700 (PDT)
From: Huacai Chen <chenhc@lemote.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Thomas Bogendoerfer <tsbogend@alpha.franken.de>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>
Cc: kvm@vger.kernel.org, linux-mips@vger.kernel.org,
        Fuxin Zhang <zhangfx@lemote.com>,
        Huacai Chen <chenhuacai@gmail.com>,
        Jiaxun Yang <jiaxun.yang@flygoat.com>,
        Huacai Chen <chenhc@lemote.com>
Subject: [PATCH] KVM: MIPS: Fix build errors for 32bit kernel
Date: Fri, 10 Jul 2020 15:23:17 +0800
Message-Id: <1594365797-536-1-git-send-email-chenhc@lemote.com>
X-Mailer: git-send-email 2.7.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit dc6d95b153e78ed70b1b2c04a ("KVM: MIPS: Add more MMIO load/store
instructions emulation") introduced some 64bit load/store instructions
emulation which are unavailable on 32bit platform, and it causes build
errors:

arch/mips/kvm/emulate.c: In function 'kvm_mips_emulate_store':
arch/mips/kvm/emulate.c:1734:6: error: right shift count >= width of type [-Werror]
      ((vcpu->arch.gprs[rt] >> 56) & 0xff);
      ^
arch/mips/kvm/emulate.c:1738:6: error: right shift count >= width of type [-Werror]
      ((vcpu->arch.gprs[rt] >> 48) & 0xffff);
      ^
arch/mips/kvm/emulate.c:1742:6: error: right shift count >= width of type [-Werror]
      ((vcpu->arch.gprs[rt] >> 40) & 0xffffff);
      ^
arch/mips/kvm/emulate.c:1746:6: error: right shift count >= width of type [-Werror]
      ((vcpu->arch.gprs[rt] >> 32) & 0xffffffff);
      ^
arch/mips/kvm/emulate.c:1796:6: error: left shift count >= width of type [-Werror]
      (vcpu->arch.gprs[rt] << 32);
      ^
arch/mips/kvm/emulate.c:1800:6: error: left shift count >= width of type [-Werror]
      (vcpu->arch.gprs[rt] << 40);
      ^
arch/mips/kvm/emulate.c:1804:6: error: left shift count >= width of type [-Werror]
      (vcpu->arch.gprs[rt] << 48);
      ^
arch/mips/kvm/emulate.c:1808:6: error: left shift count >= width of type [-Werror]
      (vcpu->arch.gprs[rt] << 56);
      ^
cc1: all warnings being treated as errors
make[3]: *** [arch/mips/kvm/emulate.o] Error 1

So, use #if defined(CONFIG_64BIT) && defined(CONFIG_KVM_MIPS_VZ) to
guard the 64bit load/store instructions emulation.

Reported-by: kernel test robot <lkp@intel.com>
Fixes: dc6d95b153e78ed70b1b2c04a ("KVM: MIPS: Add more MMIO load/store instructions emulation")
Signed-off-by: Huacai Chen <chenhc@lemote.com>
---
 arch/mips/kvm/emulate.c | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [PATCH v4 1/9] KVM: nSVM: split kvm_init_shadow_npt_mmu() from kvm_init_shadow_mmu()
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11656755
Return-Path: <SRS0=WjKu=AV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 87FC2913
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jul 2020 14:12:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6D73B207D0
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jul 2020 14:12:10 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="IrqIqMWj"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728098AbgGJOMJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 10 Jul 2020 10:12:09 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:39419 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726496AbgGJOMI (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 10 Jul 2020 10:12:08 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1594390326;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=kJ/JziJt1YuU460LMs6g6+REDy7/ZU1qE5RQxXXNeeA=;
        b=IrqIqMWj7aJp2QzoA0O1NQFhREOCGyNlZHWapvZNYsDB0/t8mAloEtL/ZjjDOQAgvwl3sX
        0l26AycHxU/hC2fgend9Zk8qfXp+MVc4BQFv+LUjM5Bmdq4eqtR2oOGkZ0Y/GrQ1QNeeUP
        BjTCepvfjzgMf66bXcM24CP0iqwOSaw=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-492-DkLM4h1kN6WaeiJ5MQ8dLw-1; Fri, 10 Jul 2020 10:12:05 -0400
X-MC-Unique: DkLM4h1kN6WaeiJ5MQ8dLw-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 09306102C7F3;
        Fri, 10 Jul 2020 14:12:04 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.35])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E80F974F44;
        Fri, 10 Jul 2020 14:12:01 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Junaid Shahid <junaids@google.com>,
        linux-kernel@vger.kernel.org
Subject: [PATCH v4 1/9] KVM: nSVM: split kvm_init_shadow_npt_mmu() from
 kvm_init_shadow_mmu()
Date: Fri, 10 Jul 2020 16:11:49 +0200
Message-Id: <20200710141157.1640173-2-vkuznets@redhat.com>
In-Reply-To: <20200710141157.1640173-1-vkuznets@redhat.com>
References: <20200710141157.1640173-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

As a preparatory change for moving kvm_mmu_new_pgd() from
nested_prepare_vmcb_save() to nested_svm_init_mmu_context() split
kvm_init_shadow_npt_mmu() from kvm_init_shadow_mmu(). This also makes
the code look more like nVMX (kvm_init_shadow_ept_mmu()).

No functional change intended.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/mmu.h        |  3 ++-
 arch/x86/kvm/mmu/mmu.c    | 31 ++++++++++++++++++++++++-------
 arch/x86/kvm/svm/nested.c |  3 ++-
 3 files changed, 28 insertions(+), 9 deletions(-)

```
#### [PATCH] KVM: nSVM: remove nonsensical EXITINFO1 adjustment on nested NPF
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11657401
Return-Path: <SRS0=WjKu=AV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8F33913BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jul 2020 20:51:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 69306207DF
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jul 2020 20:51:15 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="XSbRjJiZ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727101AbgGJUvL (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 10 Jul 2020 16:51:11 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:26923 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726965AbgGJUvL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 10 Jul 2020 16:51:11 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1594414270;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=nYaxZ7g1kLsIpQ2YHr1Z0FbzS/d7X/Lb2qWm2o336oM=;
        b=XSbRjJiZ19WXfpf+1JO7wsUP2JXy+KYMqKYIrqE3RWu2jiQjqvYSQ5cUpln6aUd02ALAwa
        XXwLjJZ7MHKZf2UQ/tYTo7rGTQLRkHf/EYVxY3F7mp2jvvqfJaa6TFNfCFawGx54KCpS0p
        XjiDsZt3tdmS4i+UkGuhRoRy8EBv6+0=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-409-n35QQoVkMbqzxCc70t8gaA-1; Fri, 10 Jul 2020 16:51:08 -0400
X-MC-Unique: n35QQoVkMbqzxCc70t8gaA-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 3B56280183C;
        Fri, 10 Jul 2020 20:51:07 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id B5C7B10013C4;
        Fri, 10 Jul 2020 20:51:06 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Nadav Amit <namit@vmware.com>
Subject: [PATCH] KVM: nSVM: remove nonsensical EXITINFO1 adjustment on nested
 NPF
Date: Fri, 10 Jul 2020 16:51:06 -0400
Message-Id: <20200710205106.941151-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The "if" that drops the present bit from the page structure fauls makes no sense.
It was added by yours truly in order to be bug-compatible with pre-existing code
and in order to make the tests pass; however, the tests are wrong.  The behavior
after this patch matches bare metal.

Reported-by: Nadav Amit <namit@vmware.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/svm/nested.c | 7 -------
 1 file changed, 7 deletions(-)

```
#### [PATCH v13 01/17] RISC-V: Add hypervisor extension related CSR defines
##### From: Anup Patel <anup.patel@wdc.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Anup Patel <Anup.Patel@wdc.com>
X-Patchwork-Id: 11655987
Return-Path: <SRS0=WjKu=AV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2CB1914B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jul 2020 08:26:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0CE12207F9
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jul 2020 08:26:34 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=wdc.com header.i=@wdc.com header.b="B4G3Uox/";
	dkim=pass (1024-bit key) header.d=sharedspace.onmicrosoft.com
 header.i=@sharedspace.onmicrosoft.com header.b="B4sYlP7e"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727005AbgGJI0a (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 10 Jul 2020 04:26:30 -0400
Received: from esa1.hgst.iphmx.com ([68.232.141.245]:47933 "EHLO
        esa1.hgst.iphmx.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726921AbgGJI03 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 10 Jul 2020 04:26:29 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple;
  d=wdc.com; i=@wdc.com; q=dns/txt; s=dkim.wdc.com;
  t=1594369589; x=1625905589;
  h=from:to:cc:subject:date:message-id:in-reply-to:
   references:content-transfer-encoding:mime-version;
  bh=ojHfcW9Gih78EJlqriXyMmYTKPT1xmuoIW6UQJAU9nU=;
  b=B4G3Uox/DGYsAsduC031W1Pz0JZbLXnD0H2RdL5HNRMqgKItHd+RUOU8
   qmXwSU2wnZyMElHbo6ub70ayNK3uGxSrXMLcD14YoK8ybaVFmhKfPLnek
   1MqaOS8XbrTm2f4oSnUvqsg0S9KeJpw6V7/O8boYELro5/C1ko/nCHIMe
   rGbezWoGKqqoagfBF2AeKrFO0IP5YlX4F1llV6/jUuMqqm/AEdBRitqIH
   392xJgT8onNQ+UEixFZTZr37JEVg2DXQUql1YVz5sWiuFUlzURDT1zN1u
   qmp5b3bmg4j3Ygng0ixKtDaUpMmdkx6AEmWmyCZHfw7TsWDRemxohUBpR
   A==;
IronPort-SDR: 
 d1hT8AHPZl85pxJf7cO1DeZ/mTF2ItLlq5DJhJXvU9yRZOYQW2MzK2AcpRtgKy9/AmyVguzlC0
 +MiW+8b4gMIVfpvt/wC4w2huNSuRzt/55VB+aEMgAUh+eJLcOewJcMr2LVgt4dczuRuGHKdmwK
 FCcOFFx9JFIzdLBtklYUboxQSvgRMC0TDmKdYZAeXPFA7WkxN+t1SNav2ujAC4HHoY5dkDSrHW
 BDnbDxE1PaMkx5BLQ/mJ4gKA1T71+AR0xQzFdLIE9kg9G6aZMKCC5d4Wc3rKwWOcBxKpDHK7fG
 v/4=
X-IronPort-AV: E=Sophos;i="5.75,335,1589212800";
   d="scan'208";a="251355477"
Received: from mail-bn8nam11lp2170.outbound.protection.outlook.com (HELO
 NAM11-BN8-obe.outbound.protection.outlook.com) ([104.47.58.170])
  by ob1.hgst.iphmx.com with ESMTP; 10 Jul 2020 16:26:27 +0800
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=Kp/JU4uIDv0LZNAoqGvMAxA6Jw2Un4RaymBfqCBvTFftgdc3B8THVQQAEJa5yqnlglq2JAA7nzy/slud7Lbismq75lisJyMi1PBEUs79gJnhAGqJhO7UvwkpqM3FQHXAAPmVJedZNQRtCE51wzIUvG8m6sdsBxdZK4wSDkm30pX5HPxIEb+1HKedDenLTioV9I017aWtRkSfcBUy9Y1SEnmO0hKd8BoTszvRg32KE/kuQQRJppw/rAqoUKllhXixp/Ndw489aWI3fsxBjzoFhaFKEVaiTHWt4YvRnFu1I3CuGxbBYZFQrxqrei54QvWO6y9SRnCosCZfM3W3PQVghA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=E6yCZpgrKYLXHvQFIUlHmHasOYuJslISWAqG8lfny/E=;
 b=Y0RutgLazRUEPmiO5r/AnpprnIgSHNH1CdsrrUinC/UVjaA3cf+WdGVmNW3NA38TOxAsZ7EIiI2gk+bG2NgKef/Jvxor7MERYvhclaFvwN1y6fNtOPKvz4HQBUewv7akehMd8/UTMj/GnhOObD74Sn9FDEZNQNeLoU6I/Qfqfq0fUjHXPAmviRUQ9eHdFelFc8HqAXgDa9D6WIMYBODvTeB+PzPV1T9t1A8/bED9huf1a1c7YAKRYAVMtL4MCNdd2OBKeUQqBcoeGC+vO9/AEAdu1bYUb79V4Xlgt01DW6OYMctbS/q7PmF3aYQOoxbmvX3fE2t3gsSg28tDGlFGGg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=wdc.com; dmarc=pass action=none header.from=wdc.com; dkim=pass
 header.d=wdc.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=sharedspace.onmicrosoft.com; s=selector2-sharedspace-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=E6yCZpgrKYLXHvQFIUlHmHasOYuJslISWAqG8lfny/E=;
 b=B4sYlP7e0q30d3ISRX4RBdCOc+IUQtc2h+zo4vjXnV+MhxYErwegQM5lmwJ1+Gcywf0M/6a/uHL4TvW0ykd1f0/JAlD4jo+Xoq6+hDFFst5Y5vRgiLVttO2koVBzUXjKzZ+xk3Ih2wgdMaoKt/WIM0CL+5anjWJGBYLJ/E1K3g4=
Authentication-Results: dabbelt.com; dkim=none (message not signed)
 header.d=none;dabbelt.com; dmarc=none action=none header.from=wdc.com;
Received: from DM6PR04MB6201.namprd04.prod.outlook.com (2603:10b6:5:127::32)
 by DM5PR04MB0461.namprd04.prod.outlook.com (2603:10b6:3:ab::22) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3153.22; Fri, 10 Jul
 2020 08:26:26 +0000
Received: from DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::e0a4:aa82:1847:dea5]) by DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::e0a4:aa82:1847:dea5%7]) with mapi id 15.20.3174.023; Fri, 10 Jul 2020
 08:26:26 +0000
From: Anup Patel <anup.patel@wdc.com>
To: Palmer Dabbelt <palmer@dabbelt.com>,
        Palmer Dabbelt <palmerdabbelt@google.com>,
        Paul Walmsley <paul.walmsley@sifive.com>,
        Albert Ou <aou@eecs.berkeley.edu>,
        Paolo Bonzini <pbonzini@redhat.com>
Cc: Alexander Graf <graf@amazon.com>,
        Atish Patra <atish.patra@wdc.com>,
        Alistair Francis <Alistair.Francis@wdc.com>,
        Damien Le Moal <damien.lemoal@wdc.com>,
        Anup Patel <anup@brainfault.org>, kvm@vger.kernel.org,
        kvm-riscv@lists.infradead.org, linux-riscv@lists.infradead.org,
        linux-kernel@vger.kernel.org, Anup Patel <anup.patel@wdc.com>
Subject: [PATCH v13 01/17] RISC-V: Add hypervisor extension related CSR
 defines
Date: Fri, 10 Jul 2020 13:55:32 +0530
Message-Id: <20200710082548.123180-2-anup.patel@wdc.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20200710082548.123180-1-anup.patel@wdc.com>
References: <20200710082548.123180-1-anup.patel@wdc.com>
X-ClientProxiedBy: PN1PR0101CA0035.INDPRD01.PROD.OUTLOOK.COM
 (2603:1096:c00:c::21) To DM6PR04MB6201.namprd04.prod.outlook.com
 (2603:10b6:5:127::32)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from wdc.com (103.15.57.207) by
 PN1PR0101CA0035.INDPRD01.PROD.OUTLOOK.COM (2603:1096:c00:c::21) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3174.20 via Frontend
 Transport; Fri, 10 Jul 2020 08:26:21 +0000
X-Mailer: git-send-email 2.25.1
X-Originating-IP: [103.15.57.207]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: f636482d-0b28-40ea-085e-08d824aaefb9
X-MS-TrafficTypeDiagnostic: DM5PR04MB0461:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM5PR04MB04616C61F1EC276A950B61C48D650@DM5PR04MB0461.namprd04.prod.outlook.com>
WDCIPOUTBOUND: EOP-TRUE
X-MS-Oob-TLC-OOBClassifiers: OLM:11;
X-Forefront-PRVS: 046060344D
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 V3JbZePIJqyMPOH/PTI0oEH2UIJCybkNUsRxY+n+KIEbkbDuNyV3Ahtt0JPSm7sFjRcHNqdsTcr8VHJVoQJIealKZBb7rXc9Dv93InHS2iYXFaf01X45PoehhG3gm/Xm285jitb6J/UJWt33zW9jw5EyeISP/NkLlAyGK/CYvTVYoX2doa6iJkNaTzPlBCdze+XNDqLiibYfwk983+u/k0/c+U9D75bMGBUPTjoY7rF1HqCdtDM+cZk5ZMTT092h2/jWKquMwX4tA7rxo6sSu9VrQjqW336pm9AoiOdjVThm6CKbSZwErlrqtq3KsHp1l7TdqUF5Mwf4XVxV4fl1xw==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR04MB6201.namprd04.prod.outlook.com;PTR:;CAT:NONE;SFTY:;SFS:(4636009)(366004)(39860400002)(136003)(376002)(396003)(346002)(2906002)(316002)(83380400001)(110136005)(54906003)(7416002)(478600001)(6666004)(86362001)(8936002)(5660300002)(7696005)(4326008)(2616005)(26005)(956004)(52116002)(8886007)(8676002)(186003)(66946007)(66476007)(55016002)(36756003)(66556008)(44832011)(16526019)(1076003);DIR:OUT;SFP:1102;
X-MS-Exchange-AntiSpam-MessageData: 
 9OxbczUIEUOwubo6JRAmUo7rPbAVbegbVbj22edBqDMCdst6t3XxZpoSXyLZ29etNM56G2wH6S1neZIVaktDn/46pcVmSVGX8P9jNArDPGqOFTAvs6WKQuiJcfgt4EHiRI8jGZDEbueYEGKBJ/rOeAVefRz6Ta0jf1vbUA3HKvncGkrVsx4KnI4ut8sPI3Z893DmeUlE3tNK+DlTAMSJ0yGDfTmOQjBaUXChOQmf2mNr1cDlKtGw4fGFiHMd9zeZ/x0i6+9IGNztpHM2SLnbD2ZO0J7yHEcDCZ+DzJyUogzQGXBLk0i+gI5pd8ag0wbLjZZCjTZD/TtkdkEemuLUKbxbpR1lFOukSznCGj/6mrUr6Uw2ZMbjweFwUcyBkyuOGJRl8vf1m8ll8gb2yTdVb+xf1IHIfVMowWDgVzMNq/3Ed2g3xi7KdkaP7jTxKquN7LuHw6Irt1/CDkwMzUna03HUnTm1/UJrvkcaNWKJsf4=
X-OriginatorOrg: wdc.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 f636482d-0b28-40ea-085e-08d824aaefb9
X-MS-Exchange-CrossTenant-AuthSource: DM6PR04MB6201.namprd04.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 10 Jul 2020 08:26:26.0834
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: b61c8803-16f3-4c35-9b17-6f65f441df86
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 IDIYImKHMxh64XxJkDq1atJR50B1Hm7qWaI2WPZe+8f8UPBJvu8SjaFuW2Da6lvamQgCxqxJv7IUdsbyjzX0kw==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM5PR04MB0461
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch extends asm/csr.h by adding RISC-V hypervisor extension
related defines.

Signed-off-by: Anup Patel <anup.patel@wdc.com>
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Alexander Graf <graf@amazon.com>
---
 arch/riscv/include/asm/csr.h | 87 ++++++++++++++++++++++++++++++++++++
 1 file changed, 87 insertions(+)

```
#### [PATCH v3 1/9] KVM: x86: Add helper functions for illegal GPA checking and page fault injection
##### From: Mohammed Gamal <mgamal@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Mohammed Gamal <mgamal@redhat.com>
X-Patchwork-Id: 11656887
Return-Path: <SRS0=WjKu=AV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 905826C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jul 2020 15:48:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7726120748
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jul 2020 15:48:31 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="RCHrNlSM"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728097AbgGJPs1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 10 Jul 2020 11:48:27 -0400
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:50247 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728067AbgGJPs0 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 10 Jul 2020 11:48:26 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1594396104;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=wqDUf4G2rfZBuLfI9I+dpuh0XkyA1XBdq/H6K7aU6xQ=;
        b=RCHrNlSMv4HDtwFwYrKLC8ACEfUrQIFiDvFrUIx+5pnUQMN/0OLB4+Yd6P1m+OEKiPWr+2
        /cuLOdb7b+5MHldXFe1GL7n/LmKGZAwDF+u5CatxW1YWUbWbFjoaodrPVi4oOFNXYf70wd
        hwTcjtdwx6uoJH0aiyhYlfKZlZKFvdU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-51-kVY0tH_8MauYwOmatmaAkA-1; Fri, 10 Jul 2020 11:48:23 -0400
X-MC-Unique: kVY0tH_8MauYwOmatmaAkA-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id A8BC9106B24C;
        Fri, 10 Jul 2020 15:48:21 +0000 (UTC)
Received: from localhost.localdomain.com (ovpn-114-235.ams2.redhat.com
 [10.36.114.235])
        by smtp.corp.redhat.com (Postfix) with ESMTP id B0A787EFA3;
        Fri, 10 Jul 2020 15:48:19 +0000 (UTC)
From: Mohammed Gamal <mgamal@redhat.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: linux-kernel@vger.kernel.org, vkuznets@redhat.com,
        sean.j.christopherson@intel.com, wanpengli@tencent.com,
        jmattson@google.com, joro@8bytes.org,
        Mohammed Gamal <mgamal@redhat.com>
Subject: [PATCH v3 1/9] KVM: x86: Add helper functions for illegal GPA
 checking and page fault injection
Date: Fri, 10 Jul 2020 17:48:03 +0200
Message-Id: <20200710154811.418214-2-mgamal@redhat.com>
In-Reply-To: <20200710154811.418214-1-mgamal@redhat.com>
References: <20200710154811.418214-1-mgamal@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch adds two helper functions that will be used to support virtualizing
MAXPHYADDR in both kvm-intel.ko and kvm.ko.

kvm_fixup_and_inject_pf_error() injects a page fault for a user-specified GVA,
while kvm_mmu_is_illegal_gpa() checks whether a GPA exceeds vCPU address limits.

Signed-off-by: Mohammed Gamal <mgamal@redhat.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/mmu.h |  6 ++++++
 arch/x86/kvm/x86.c | 21 +++++++++++++++++++++
 arch/x86/kvm/x86.h |  1 +
 3 files changed, 28 insertions(+)

```
#### [RFC PATCH v4 1/8] update_headers: Sync-up ABI headers with Linux-5.8-rc4
##### From: Anup Patel <anup.patel@wdc.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Anup Patel <Anup.Patel@wdc.com>
X-Patchwork-Id: 11656061
Return-Path: <SRS0=WjKu=AV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6900B13B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jul 2020 09:01:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 41588207F9
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jul 2020 09:01:09 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=wdc.com header.i=@wdc.com header.b="Q2sTbIWt";
	dkim=pass (1024-bit key) header.d=sharedspace.onmicrosoft.com
 header.i=@sharedspace.onmicrosoft.com header.b="u3E1iQLo"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727972AbgGJJBI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 10 Jul 2020 05:01:08 -0400
Received: from esa4.hgst.iphmx.com ([216.71.154.42]:6017 "EHLO
        esa4.hgst.iphmx.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726496AbgGJJBH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 10 Jul 2020 05:01:07 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple;
  d=wdc.com; i=@wdc.com; q=dns/txt; s=dkim.wdc.com;
  t=1594371666; x=1625907666;
  h=from:to:cc:subject:date:message-id:in-reply-to:
   references:content-transfer-encoding:mime-version;
  bh=1yJNVc5F5ocDUnVzKDAoiFjtAHcMgx1NxHiuyVmJjIw=;
  b=Q2sTbIWtiYRZqZ6vSI7iewUKnM61zYUwoq3iFcdQC7JkVryptpoQ821E
   azL/7MBezLeCN6i6ZJ41gRZLY0BZFXQiD37z9E8JX/lzOIMKj4JgI7Rz1
   oryCMh7CCm+c4lW+924czMgrHRdWP6Gl8aGS0wAKOeNNEVqtjyxAJBWp/
   WarJCq5VegdSxMmFVXOTH5muDwzrRpwRcyKS6a+U4FeW76IHbP0QhPBoQ
   7A5w1bj2wdwhKVAN0+dlDPoeTMKABXPeyxvJ13XLp5Zuj++1qFdsHQoV4
   pOY6r9vzWNEjNDB/SzK+9H6IIkcBp6Kzx13bmevdgol9EKL9UIgip1S+Y
   Q==;
IronPort-SDR: 
 Ia3zdilR+p8wUA9YrzmStyjgbX4Zh525fWGZDePa9mhHMIQXe/0jz5oe7yv7g69TndNHiklnKm
 HxUreJurRbCYTnFhHRYhi1bd8J9D0aS8jVPPu9w3j9XR2rBBXhYkI3ZkydGKCiD6OZxAXDBDBZ
 JleqxMoS0BWysnSZZhn1ZkZpCOd7KUVtnAuCLiCjPEvesSzIeQiy9gzDMn3kqTLkx4+ku4oM+w
 VcYDZlcNHgJRhCsUrQGiSFyA7mCSZBdNVQE5fUP+Lc4IhK1uGg+qw3HV5v4r0JUwD2k1MKp6Qk
 s/A=
X-IronPort-AV: E=Sophos;i="5.75,335,1589212800";
   d="scan'208";a="142124232"
Received: from mail-bn8nam12lp2174.outbound.protection.outlook.com (HELO
 NAM12-BN8-obe.outbound.protection.outlook.com) ([104.47.55.174])
  by ob1.hgst.iphmx.com with ESMTP; 10 Jul 2020 17:01:05 +0800
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=hR+rjyYA+MoZZC0/QmaGynWb57E6W0papnoIH80ycbLvJm0jQtMwZ9ibE3OKki+sxVHdozpwjCYmOysrdY74rvUrO6EUZBAieMnGF9QVaAK0kp+30JetLHcjUUIYKVwGQh2Q6zX5rAzPjcDCZQtl4UuWSi3/29H6ZDpE8HrhCll+VJiU2X/gbdr7hnK0nuL/bwqpWI6uTJeIl3/xuM2zcRrsoam0qqOOH7pzSS1OnlJ5H1pOq30X1aziEOBuN0hCyHsNU06P1Uq9V9aa68nIxpFXP4NUZ4A42/7mmoFJFr+Hg03T6WsBar4Vl1+9PBhqwL7/Fq0d+A/widGGofYV3A==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=sM6xoNCkuode0NTqCUyKLHzwkeQud7yZAilxdSRMLvQ=;
 b=n6H9sFpajD21j9ndxM9I2EecypYfhkHM0DJp8WFASeUQrNlzldJOsREKXQ9jVJG5U4iOfyPK6eMO4UVf6gaN7+ieBsKCa/0d3EvR1hdpn4UQDMhjeDIlZl2eiqIJhOfxi0OzaM3hNAErnKrfK1UCyc5S6tmVpWQ4abd/TDlcmkOoGc6G993CDWdHMLE+QTSMcDGcVI/P5TvHfeh8A1TuD/P6FW0FwkD2RYq84VZ9TXLKcbFHChh8oHd/il0F0tdsDh9gOqI8IpOem3aUATpH/1NRpp4bJ5Umr93XBD0ZxvkxQROH+1d9Dn9I5/C4YIF6pDmjLzLOkuFPXxqWa/7wQA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=wdc.com; dmarc=pass action=none header.from=wdc.com; dkim=pass
 header.d=wdc.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=sharedspace.onmicrosoft.com; s=selector2-sharedspace-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=sM6xoNCkuode0NTqCUyKLHzwkeQud7yZAilxdSRMLvQ=;
 b=u3E1iQLovn1LqySV4pzkzcbd9elApdF9gTqoFt/rB9o6fSPT6j8i7Gqj368gh2PIIScSkdwK49lO0OvUUcyr/4mClVYRB8/SF77CO+8RKyruRwU2J65AHy3V67a01MzMfs4CKfrA4mW19HzD4V/edugNE1bh1AqNEsiTmRS3kHE=
Authentication-Results: kernel.org; dkim=none (message not signed)
 header.d=none;kernel.org; dmarc=none action=none header.from=wdc.com;
Received: from DM6PR04MB6201.namprd04.prod.outlook.com (2603:10b6:5:127::32)
 by DM5PR04MB0346.namprd04.prod.outlook.com (2603:10b6:3:6f::7) with Microsoft
 SMTP Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.3174.21; Fri, 10 Jul 2020 09:01:04 +0000
Received: from DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::e0a4:aa82:1847:dea5]) by DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::e0a4:aa82:1847:dea5%7]) with mapi id 15.20.3174.023; Fri, 10 Jul 2020
 09:01:04 +0000
From: Anup Patel <anup.patel@wdc.com>
To: Will Deacon <will@kernel.org>
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Atish Patra <atish.patra@wdc.com>,
        Alistair Francis <Alistair.Francis@wdc.com>,
        Anup Patel <anup@brainfault.org>, kvm@vger.kernel.org,
        kvm-riscv@lists.infradead.org, Anup Patel <anup.patel@wdc.com>
Subject: [RFC PATCH v4 1/8] update_headers: Sync-up ABI headers with
 Linux-5.8-rc4
Date: Fri, 10 Jul 2020 14:30:28 +0530
Message-Id: <20200710090035.123941-2-anup.patel@wdc.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20200710090035.123941-1-anup.patel@wdc.com>
References: <20200710090035.123941-1-anup.patel@wdc.com>
X-ClientProxiedBy: PN1PR0101CA0029.INDPRD01.PROD.OUTLOOK.COM
 (2603:1096:c00:c::15) To DM6PR04MB6201.namprd04.prod.outlook.com
 (2603:10b6:5:127::32)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from wdc.com (103.15.57.207) by
 PN1PR0101CA0029.INDPRD01.PROD.OUTLOOK.COM (2603:1096:c00:c::15) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3174.21 via Frontend
 Transport; Fri, 10 Jul 2020 09:01:00 +0000
X-Mailer: git-send-email 2.25.1
X-Originating-IP: [103.15.57.207]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: da6dad3a-8af8-4161-dcf4-08d824afc639
X-MS-TrafficTypeDiagnostic: DM5PR04MB0346:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM5PR04MB0346D7C230244F0B082A92098D650@DM5PR04MB0346.namprd04.prod.outlook.com>
WDCIPOUTBOUND: EOP-TRUE
X-MS-Oob-TLC-OOBClassifiers: OLM:224;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 P/7q5rxl65gBYn0a5mu9DqHnZGJaDzV/QlrwW0/aBUWm+Cb8vhgIMefYGK4er4Q5Gnu3ZCn5OQZO+WdTgCunmza5zl0piA0kHjz0jwFE0LiA+NIijw+hOBmo7KPYfvWZwQQyz+6VWSCg2lYmnDWeOB56wmX7l0Fmr8DDM+onsvQAxDzqiQm5hjh2giFERHlYZ4LYOF9DeB6Bu4bEgp++caNr9UAszxPLQ4Bl3In1rCpplbUKsa/VfbbOvgSuFv+docQHPiADQEIrEKSIv0IkrdrMLB+nnGeHrnPw5JM9ihpnlVmWp4MvYrfiQDvzXHo2
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR04MB6201.namprd04.prod.outlook.com;PTR:;CAT:NONE;SFTY:;SFS:(4636009)(396003)(346002)(136003)(366004)(376002)(39860400002)(66476007)(186003)(66556008)(16526019)(6666004)(30864003)(52116002)(8886007)(1076003)(6916009)(86362001)(7696005)(36756003)(26005)(66946007)(4326008)(5660300002)(8936002)(956004)(2906002)(2616005)(83380400001)(55016002)(478600001)(316002)(44832011)(8676002)(54906003);DIR:OUT;SFP:1102;
X-MS-Exchange-AntiSpam-MessageData: 
 I9TywHXzsyXiZhJ4M4W5yGCkvC0Fnjsn8fMpxT7ZydoKD7v3on+w8VaVJ1fsO+r42gb1dzROZHSwOfz1UhEgo7zQfDoTVi1CpDe9sR48jt4UMKjgTkimiWk4owZIzUDYUPJ85on1pUxyXZB4FsXHhMNNmJK/BbmG5+NSv/raHhs0ntG6XEICPTj8dIIl6iGyeF4m0VrTcqFS7jN3a5JiaJKmWDFXaLDu1UQ+y9re4iGVCEPDEErmOIPF+e9DvgvKg5ebWk9Y8tAZKsefyBWh5ealPjbAFjLbea+JTdYOQql0Hgdoc76iJ01sCQc81E2JRERVCZBiAvpTQ0tdYLuLiI0LY5OeNlnhz5c50FZk/ajAGbfD7E8DogF60FSb0X6WSrO4lLOkSmwCvZpt0edX0unhvz2IDs26ZIo8AQ3YXit1t6K97S7dFGSOE+HhUu6tmnJOBbMOfj/BE0dMiA11ubU8/nDOp5XahDI8RAlxESs=
X-OriginatorOrg: wdc.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 da6dad3a-8af8-4161-dcf4-08d824afc639
X-MS-Exchange-CrossTenant-AuthSource: DM6PR04MB6201.namprd04.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 10 Jul 2020 09:01:03.8421
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: b61c8803-16f3-4c35-9b17-6f65f441df86
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 sGOvE6e0xKjUdk7BVnX+qEdHfAih7NZel2GkFG01yzHbk36I7e3EgzyxIczu3B+SdKt6vEl2Oue1QX9/Vq5M3Q==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM5PR04MB0346
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We sync-up all ABI headers with Linux-5.8-rc4. This will allow
us to use ONE_REG interface for KVMTOOL RISC-V port.

Signed-off-by: Anup Patel <anup.patel@wdc.com>
---
 arm/aarch64/include/asm/kvm.h | 21 ++++++--
 include/linux/kvm.h           | 95 +++++++++++++++++++++++++++++++++--
 powerpc/include/asm/kvm.h     |  3 ++
 x86/include/asm/kvm.h         | 21 +++++++-
 4 files changed, 131 insertions(+), 9 deletions(-)

```
#### [RFC PATCH 1/3] MIPS: Retire kvm paravirt
##### From: Jiaxun Yang <jiaxun.yang@flygoat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jiaxun Yang <jiaxun.yang@flygoat.com>
X-Patchwork-Id: 11655793
Return-Path: <SRS0=WjKu=AV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4D12414E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jul 2020 06:33:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2333420787
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jul 2020 06:33:00 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=flygoat.com header.i=@flygoat.com header.b="Lt7K31Ij"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727085AbgGJGc7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 10 Jul 2020 02:32:59 -0400
Received: from vultr.net.flygoat.com ([149.28.68.211]:40632 "EHLO
        vultr.net.flygoat.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726004AbgGJGc7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 10 Jul 2020 02:32:59 -0400
Received: from localhost.localdomain (unknown
 [IPv6:2001:da8:20f:4430:250:56ff:fe9a:7470])
        by vultr.net.flygoat.com (Postfix) with ESMTPSA id 357FD1FF15;
        Fri, 10 Jul 2020 06:32:55 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple; d=flygoat.com; s=vultr;
        t=1594362778; bh=dbezDAzQUO6V7Qt4rnIubgoAOGxRnzf2dCmnywT7xOA=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=Lt7K31IjObfbcEsrNoTiYzLoeHjB8U3wtMXmtYgEgKGcJnuMaKQoDVUrh5tBZXCyE
         Ut3zbv38HMqhoVjlXLE/T4ZyJ7jcNh6kMnFRxmAumBfOJ25WuTcodC2KeL/BxCxXAg
         7mWm1Vw6f0BpETrShwHjuU9EYbaJEa8EIc51raY6Wxmgp1NkcBMmujGok96Qe7KTbp
         h9TeXtn9m+0d6M25tOnOg1smDaHejunp3VCLj/J9SlMYeR6UHo4bzGF+Fg5tNdez/R
         K+foYaiap/5mULCu7vnCx80iUIREYDNLYRHbeZvHkxlSY8OBhMlV7DpBF4rXKglxHJ
         D+hlAzweJrGSA==
From: Jiaxun Yang <jiaxun.yang@flygoat.com>
To: linux-mips@vger.kernel.org
Cc: Jiaxun Yang <jiaxun.yang@flygoat.com>,
        Thomas Bogendoerfer <tsbogend@alpha.franken.de>,
        Michal Simek <michal.simek@xilinx.com>,
        Paul Walmsley <paul.walmsley@sifive.com>,
        Masahiro Yamada <masahiroy@kernel.org>,
        Waiman Long <longman@redhat.com>,
        Andrew Morton <akpm@linux-foundation.org>,
        Alexander Lobakin <alobakin@pm.me>,
        Jason Wang <jasowang@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Huacai Chen <chenhc@lemote.com>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>,
        Paul Burton <paulburton@kernel.org>,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [RFC PATCH 1/3] MIPS: Retire kvm paravirt
Date: Fri, 10 Jul 2020 14:30:16 +0800
Message-Id: <20200710063047.154611-2-jiaxun.yang@flygoat.com>
X-Mailer: git-send-email 2.27.0
In-Reply-To: <20200710063047.154611-1-jiaxun.yang@flygoat.com>
References: <20200710063047.154611-1-jiaxun.yang@flygoat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

paravirt machine was introduced for Cavium's partial virtualization
technology, however, it's host side support and QEMU support never
landed in upstream.

As Cavium was acquired by Marvel and they have no intention to maintain
their MIPS product line, also paravirt is unlikely to be utilized by
community users, it's time to retire it if nobody steps in to maintain
it.

Signed-off-by: Jiaxun Yang <jiaxun.yang@flygoat.com>
---
 arch/mips/Kbuild.platforms                |   1 -
 arch/mips/Kconfig                         |  19 --
 arch/mips/configs/mips_paravirt_defconfig |  98 ------
 arch/mips/include/asm/Kbuild              |   1 +
 arch/mips/include/asm/kvm_para.h          | 115 -------
 arch/mips/include/uapi/asm/Kbuild         |   2 +
 arch/mips/include/uapi/asm/kvm_para.h     |   5 -
 arch/mips/paravirt/Kconfig                |   7 -
 arch/mips/paravirt/Makefile               |  14 -
 arch/mips/paravirt/Platform               |   7 -
 arch/mips/paravirt/paravirt-irq.c         | 368 ----------------------
 arch/mips/paravirt/paravirt-smp.c         | 145 ---------
 arch/mips/paravirt/serial.c               |  39 ---
 arch/mips/paravirt/setup.c                |  67 ----
 arch/mips/pci/Makefile                    |   1 -
 arch/mips/pci/pci-virtio-guest.c          | 131 --------
 16 files changed, 3 insertions(+), 1017 deletions(-)
 delete mode 100644 arch/mips/configs/mips_paravirt_defconfig
 delete mode 100644 arch/mips/include/asm/kvm_para.h
 delete mode 100644 arch/mips/include/uapi/asm/kvm_para.h
 delete mode 100644 arch/mips/paravirt/Kconfig
 delete mode 100644 arch/mips/paravirt/Makefile
 delete mode 100644 arch/mips/paravirt/Platform
 delete mode 100644 arch/mips/paravirt/paravirt-irq.c
 delete mode 100644 arch/mips/paravirt/paravirt-smp.c
 delete mode 100644 arch/mips/paravirt/serial.c
 delete mode 100644 arch/mips/paravirt/setup.c
 delete mode 100644 arch/mips/pci/pci-virtio-guest.c

```
#### [PATCH v3] KVM: x86: move MSR_IA32_PERF_CAPABILITIES emulation to common x86 code
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11656845
Return-Path: <SRS0=WjKu=AV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7E30F92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jul 2020 15:26:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 636E420720
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jul 2020 15:26:09 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="BU+qQX11"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727907AbgGJP0I (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 10 Jul 2020 11:26:08 -0400
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:55837 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726962AbgGJP0H (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 10 Jul 2020 11:26:07 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1594394766;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=o99/BwfqjWQiBTm39Rbe0UIfyhuvQm1bvRYJ0Q0vEoA=;
        b=BU+qQX11FD6JOrgXS/hUE1Oq4P0KVGO0fMcuqw74TP4iP0MmGYrN+5akGjTcEYqwbN1BrY
        Lp2IaN0LXx5HK3emiLt2A8E8K/PmgrU8BUPwK8w2XeQbR+K58QB7j4GcdM6QLPvL5X7UGm
        O3ds10m0nRgs6PnVg5VxZTrh/BW4Sec=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-221-nvi7qKmuMrS-LNMRnbYelg-1; Fri, 10 Jul 2020 11:26:04 -0400
X-MC-Unique: nvi7qKmuMrS-LNMRnbYelg-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 63E8B800FEB;
        Fri, 10 Jul 2020 15:26:03 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.35])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 1899960C05;
        Fri, 10 Jul 2020 15:26:00 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Like Xu <like.xu@linux.intel.com>, linux-kernel@vger.kernel.org
Subject: [PATCH v3] KVM: x86: move MSR_IA32_PERF_CAPABILITIES emulation to
 common x86 code
Date: Fri, 10 Jul 2020 17:25:59 +0200
Message-Id: <20200710152559.1645827-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

state_test/smm_test selftests are failing on AMD with:
"Unexpected result from KVM_GET_MSRS, r: 51 (failed MSR was 0x345)"

MSR_IA32_PERF_CAPABILITIES is an emulated MSR on Intel but it is not
known to AMD code, we can move the emulation to common x86 code. For
AMD, we basically just allow the host to read and write zero to the MSR.

Fixes: 27461da31089 ("KVM: x86/pmu: Support full width counting")
Suggested-by: Jim Mattson <jmattson@google.com>
Suggested-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
- This is a succesor of "[PATCH v2] KVM: SVM: emulate MSR_IA32_PERF_CAPABILITIES".
---
 arch/x86/kvm/svm/svm.c       |  2 ++
 arch/x86/kvm/vmx/pmu_intel.c | 17 -----------------
 arch/x86/kvm/x86.c           | 20 ++++++++++++++++++++
 3 files changed, 22 insertions(+), 17 deletions(-)

```
#### [PATCH] vhost/scsi: fix up req type endian-ness
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11656231
Return-Path: <SRS0=WjKu=AV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1AAAF14DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jul 2020 10:49:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F374F2078B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jul 2020 10:49:04 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="GVnyIem8"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727955AbgGJKs7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 10 Jul 2020 06:48:59 -0400
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:43632 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727943AbgGJKs6 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 10 Jul 2020 06:48:58 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1594378136;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type;
        bh=zH+SoJc9FA+IxVxr5cux+vmHnM4kK2aczPlNcB2fA0g=;
        b=GVnyIem8Rc/LebOyLDXJmWiZQrlDorG1nSYF4iG1Ku+EsaODON8fC6GBM3gFkqcHoJ5cA5
        ETuRqtgRyowzQRY0GCdbKcQ2hQPG8mtq40BIPBAtQzic0hY0mahw/gymxYmEQ6UtXHtO1F
        ppjEDPnO22gFpSxTnmSRCH6/LJxNcPY=
Received: from mail-wm1-f70.google.com (mail-wm1-f70.google.com
 [209.85.128.70]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-47-_G5YgMRyNxKkAiSjn0HnUw-1; Fri, 10 Jul 2020 06:48:55 -0400
X-MC-Unique: _G5YgMRyNxKkAiSjn0HnUw-1
Received: by mail-wm1-f70.google.com with SMTP id g138so6251258wme.7
        for <kvm@vger.kernel.org>; Fri, 10 Jul 2020 03:48:54 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition;
        bh=zH+SoJc9FA+IxVxr5cux+vmHnM4kK2aczPlNcB2fA0g=;
        b=G84nq29x4I5R81MZuU4Idsr10n7kwKLQT9A5vmSJcz+zQA91QuSVVrbiPwvbySZoNJ
         WqP5Slcjg+UfoKFwgIUK3VLW81H4T2/1MjDHekI8GgOIyYTkEGjnfFBRNKqrgBjusXMi
         MJj2QgOtzrtWA+gyHq2iVX20KJD+lsRY6xDOUmO6nkplyp3w17iGddP/IXcMnngVMtK4
         I8QxL4AFbPuKxqsUXLGpN18CqioyqJv/XELElIegZorrdw/L+T6lO1/FHMTk4hzKrPEt
         kwfYimfrMjCRd/Out8roYa464G1w/gKFS2W1mQhXGYNwYo+FpFOXyXUdJy4MA+J86vZH
         Tv4A==
X-Gm-Message-State: AOAM531uS9bHs4+oS2RQ2lerPmjzR94dvC+wvKe1iRGig7fEksVXbw02
        JBapp0jPE7c4EOrNVTgx10vkcVbRMhMR+hFxW07rfPVdzvYN/2gcWKLvYwdg92b7gAbFprHKg/m
        sTrJAcge+te9C
X-Received: by 2002:a05:6000:1143:: with SMTP id
 d3mr55214236wrx.235.1594378134132;
        Fri, 10 Jul 2020 03:48:54 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJyw4fIgUrx6Lb8RIpTWJ39EeNc2fRHHzE0+AdkrVCaNR8Aj75HUF42WJR8yehI/TNv6QqsbOQ==
X-Received: by 2002:a05:6000:1143:: with SMTP id
 d3mr55214221wrx.235.1594378133933;
        Fri, 10 Jul 2020 03:48:53 -0700 (PDT)
Received: from redhat.com (bzq-79-182-31-92.red.bezeqint.net. [79.182.31.92])
        by smtp.gmail.com with ESMTPSA id
 68sm8898710wmz.40.2020.07.10.03.48.52
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 10 Jul 2020 03:48:53 -0700 (PDT)
Date: Fri, 10 Jul 2020 06:48:51 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: stable@vger.kernel.org, Jason Wang <jasowang@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Stefan Hajnoczi <stefanha@redhat.com>,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org,
        netdev@vger.kernel.org
Subject: [PATCH] vhost/scsi: fix up req type endian-ness
Message-ID: <20200710104849.406023-1-mst@redhat.com>
MIME-Version: 1.0
Content-Disposition: inline
X-Mailer: git-send-email 2.27.0.106.g8ac3dc51b1
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

vhost/scsi doesn't handle type conversion correctly
for request type when using virtio 1.0 and up for BE,
or cross-endian platforms.

Fix it up using vhost_32_to_cpu.

Cc: stable@vger.kernel.org
Signed-off-by: Michael S. Tsirkin <mst@redhat.com>
---
 drivers/vhost/scsi.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] vsock/virtio: annotate 'the_virtio_vsock' RCU pointer
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefano Garzarella <sgarzare@redhat.com>
X-Patchwork-Id: 11656443
Return-Path: <SRS0=WjKu=AV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7582813B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jul 2020 12:13:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5C0CA2077D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jul 2020 12:13:06 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="M4TJ+oWT"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727777AbgGJMNB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 10 Jul 2020 08:13:01 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:45974 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726664AbgGJMM7 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 10 Jul 2020 08:12:59 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1594383177;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=m8g5K4VLg4BTneoyfPTMeQatQmDnDh/9EQUZe3BPx8E=;
        b=M4TJ+oWTKfPu4JklDjw1kCPjA4V4PrLDnvuVLWgA1jkII5lv6LQZZlxTZvwNLa2cUOLuyk
        eyNXjEq/TJEShUk4YF8CuetSyy7Xtszl9HjJPh3ZJH7i5ssO0+QM1HStbcQFbBDTlspDBp
        0FX/fHTJNGwONfWZEGVMfklQD2XBlaE=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-394-L0O2jgtJMHOaw7DzDpvHNQ-1; Fri, 10 Jul 2020 08:12:54 -0400
X-MC-Unique: L0O2jgtJMHOaw7DzDpvHNQ-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id BBC0B102C7F1;
        Fri, 10 Jul 2020 12:12:52 +0000 (UTC)
Received: from steredhat.redhat.com (ovpn-112-4.ams2.redhat.com [10.36.112.4])
        by smtp.corp.redhat.com (Postfix) with ESMTP id D1E0A5C6C0;
        Fri, 10 Jul 2020 12:12:44 +0000 (UTC)
From: Stefano Garzarella <sgarzare@redhat.com>
To: davem@davemloft.net
Cc: Stefano Garzarella <sgarzare@redhat.com>,
        Stefan Hajnoczi <stefanha@redhat.com>,
        virtualization@lists.linux-foundation.org,
        "Michael S. Tsirkin" <mst@redhat.com>,
        linux-kernel@vger.kernel.org, netdev@vger.kernel.org,
        Jakub Kicinski <kuba@kernel.org>, kvm@vger.kernel.org
Subject: [PATCH] vsock/virtio: annotate 'the_virtio_vsock' RCU pointer
Date: Fri, 10 Jul 2020 14:12:43 +0200
Message-Id: <20200710121243.120096-1-sgarzare@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit 0deab087b16a ("vsock/virtio: use RCU to avoid use-after-free
on the_virtio_vsock") starts to use RCU to protect 'the_virtio_vsock'
pointer, but we forgot to annotate it.

This patch adds the annotation to fix the following sparse errors:

    net/vmw_vsock/virtio_transport.c:73:17: error: incompatible types in comparison expression (different address spaces):
    net/vmw_vsock/virtio_transport.c:73:17:    struct virtio_vsock [noderef] __rcu *
    net/vmw_vsock/virtio_transport.c:73:17:    struct virtio_vsock *
    net/vmw_vsock/virtio_transport.c:171:17: error: incompatible types in comparison expression (different address spaces):
    net/vmw_vsock/virtio_transport.c:171:17:    struct virtio_vsock [noderef] __rcu *
    net/vmw_vsock/virtio_transport.c:171:17:    struct virtio_vsock *
    net/vmw_vsock/virtio_transport.c:207:17: error: incompatible types in comparison expression (different address spaces):
    net/vmw_vsock/virtio_transport.c:207:17:    struct virtio_vsock [noderef] __rcu *
    net/vmw_vsock/virtio_transport.c:207:17:    struct virtio_vsock *
    net/vmw_vsock/virtio_transport.c:561:13: error: incompatible types in comparison expression (different address spaces):
    net/vmw_vsock/virtio_transport.c:561:13:    struct virtio_vsock [noderef] __rcu *
    net/vmw_vsock/virtio_transport.c:561:13:    struct virtio_vsock *
    net/vmw_vsock/virtio_transport.c:612:9: error: incompatible types in comparison expression (different address spaces):
    net/vmw_vsock/virtio_transport.c:612:9:    struct virtio_vsock [noderef] __rcu *
    net/vmw_vsock/virtio_transport.c:612:9:    struct virtio_vsock *
    net/vmw_vsock/virtio_transport.c:631:9: error: incompatible types in comparison expression (different address spaces):
    net/vmw_vsock/virtio_transport.c:631:9:    struct virtio_vsock [noderef] __rcu *
    net/vmw_vsock/virtio_transport.c:631:9:    struct virtio_vsock *

Fixes: 0deab087b16a ("vsock/virtio: use RCU to avoid use-after-free on the_virtio_vsock")
Reported-by: Michael S. Tsirkin <mst@redhat.com>
Signed-off-by: Stefano Garzarella <sgarzare@redhat.com>
---
 net/vmw_vsock/virtio_transport.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH 1/4] x86: svm: clear CR4.DE on DR intercept test
##### From: Nadav Amit <namit@vmware.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nadav Amit <namit@vmware.com>
X-Patchwork-Id: 11657241
Return-Path: <SRS0=WjKu=AV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 47CCF17C7
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jul 2020 18:35:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 383D12078B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jul 2020 18:35:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728097AbgGJSfn (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 10 Jul 2020 14:35:43 -0400
Received: from ex13-edg-ou-002.vmware.com ([208.91.0.190]:7518 "EHLO
        EX13-EDG-OU-002.vmware.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727085AbgGJSfn (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 10 Jul 2020 14:35:43 -0400
Received: from sc9-mailhost3.vmware.com (10.113.161.73) by
 EX13-EDG-OU-002.vmware.com (10.113.208.156) with Microsoft SMTP Server id
 15.0.1156.6; Fri, 10 Jul 2020 11:35:38 -0700
Received: from sc2-haas01-esx0118.eng.vmware.com
 (sc2-haas01-esx0118.eng.vmware.com [10.172.44.118])
        by sc9-mailhost3.vmware.com (Postfix) with ESMTP id CF6EE40CA9;
        Fri, 10 Jul 2020 11:35:42 -0700 (PDT)
From: Nadav Amit <namit@vmware.com>
To: Paolo Bonzini <pbonzini@redhat.com>
CC: <kvm@vger.kernel.org>, Nadav Amit <namit@vmware.com>
Subject: [kvm-unit-tests PATCH 1/4] x86: svm: clear CR4.DE on DR intercept
 test
Date: Fri, 10 Jul 2020 11:33:17 -0700
Message-ID: <20200710183320.27266-2-namit@vmware.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200710183320.27266-1-namit@vmware.com>
References: <20200710183320.27266-1-namit@vmware.com>
MIME-Version: 1.0
Received-SPF: None (EX13-EDG-OU-002.vmware.com: namit@vmware.com does not
 designate permitted sender hosts)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

DR4/DR5 can only be written when CR4.DE is clear, and otherwise trigger
a #GP exception. The BIOS might not clear CR4.DE so update the tests not
to make this assumption.

Signed-off-by: Nadav Amit <namit@vmware.com>
Reported-by: Nadav Amit <namit@vmware.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 x86/svm_tests.c | 1 +
 1 file changed, 1 insertion(+)

```
