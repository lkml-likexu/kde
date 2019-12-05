#### [GIT PULL] Second batch of KVM changes for 5.5 merge window
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11272859
Return-Path: <SRS0=IjTT=Z2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 26657930
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Dec 2019 11:54:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 041A32084F
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Dec 2019 11:54:35 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="l50GFiDG"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727693AbfLDLyb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 4 Dec 2019 06:54:31 -0500
Received: from mail-wr1-f65.google.com ([209.85.221.65]:37333 "EHLO
        mail-wr1-f65.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727445AbfLDLyb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 4 Dec 2019 06:54:31 -0500
Received: by mail-wr1-f65.google.com with SMTP id w15so8260971wru.4;
        Wed, 04 Dec 2019 03:54:29 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=ytPbAgq8jfy9JeU4hgqnWTRgViqMNOx0ju4A9bE7cvc=;
        b=l50GFiDGVkOlKxLSE4U4bT28VrlDfrXZ0M72HBJVo2c/1IzoQjh94GnIObzj36mhjJ
         vX4kkubF5de83RdF861RMYSdCK4gW/Aoqah5Y8bSxEbj6ezEzKwbRUXbghYDoGlShEu+
         FwvEhKv6956hvUrm0LfIo+nfGvDObhKu7UJq2LG1jVqajSv+hZnKu05A6aez5ioAnMqP
         MrGd+jhNMPSTEuO2476WwH6F7xJ39Ng3X+U27XuzNfQr2CydNJXdOEj/voz0u1QPSpYQ
         itR6VxyRzu6m0YPBTeh43seIlZRMjK8J9wmPSGe7UHwSlC+mr1DQP4vCjVlqnGYPE+Op
         GUeQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=ytPbAgq8jfy9JeU4hgqnWTRgViqMNOx0ju4A9bE7cvc=;
        b=E5x1nhJUvd0rAZn6+uU9ocahzcb/R6FfW0QLooctpn5J0fVrGcJePQpLsZafWlnvGe
         xhReiUVS2Ng7PsdCXq6EhY1q5+4hub7Xtew1zejDfwIjSUYC+iGfRQsuU7U1MRvM+Qgz
         lBVdbooFR+xiUSCdIZeiizEuHiqnwzayzMwCJIA6eape5s8Asf6vhuwFEB/WOBbIPghA
         Z9k8wACFy+DjB6ysi3Z2vlM7bvMxLAm7UdYIh08SX4ks48QmVNeY3IZ+rPufFlirHWDY
         zma2voaG6Zr3s7ZNWBrBZeEG8CtMAucKj29r99lTuVpTCbpEJsT6+cbC5DgpcPs1oOdJ
         637g==
X-Gm-Message-State: APjAAAV1Gs6NPuuFgetzcpY50uUAQCf4TmWIfBoyIaWn0JatLJekt3Bb
        LUdlg61WJp+EIBDl/bT+mvoogg/S
X-Google-Smtp-Source: 
 APXvYqz3dG4Uk+JSz8YAx7xiJc5jlmHdRe2HmLe/sUlEvyLgEHQc2Uo+Uu3QMzlav/L5W5CKrOzzDg==
X-Received: by 2002:a5d:5452:: with SMTP id w18mr3422738wrv.333.1575460468945;
        Wed, 04 Dec 2019 03:54:28 -0800 (PST)
Received: from 640k.lan ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 w17sm8087952wrt.89.2019.12.04.03.54.28
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Wed, 04 Dec 2019 03:54:28 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: torvalds@linux-foundation.org
Cc: linux-kernel@vger.kernel.org, rkrcmar@kernel.org,
        kvm@vger.kernel.org
Subject: [GIT PULL] Second batch of KVM changes for 5.5 merge window
Date: Wed,  4 Dec 2019 12:54:27 +0100
Message-Id: <1575460467-29531-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linus,

The following changes since commit 96710247298df52a4b8150a62a6fe87083093ff3:

  Merge tag 'kvm-ppc-next-5.5-2' of git://git.kernel.org/pub/scm/linux/kernel/git/paulus/powerpc into HEAD (2019-11-25 11:29:05 +0100)

are available in the git repository at:


  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to 7d73710d9ca2564f29d291d0b3badc09efdf25e9:

  kvm: vmx: Stop wasting a page for guest_msrs (2019-12-04 12:23:27 +0100)

----------------------------------------------------------------
* PPC secure guest support
* small x86 cleanup
* fix for an x86-specific out-of-bounds write on a ioctl (not guest triggerable,
  data not attacker-controlled)

----------------------------------------------------------------
Anshuman Khandual (1):
      powerpc: Ultravisor: Add PPC_UV config option

Bharata B Rao (6):
      mm: ksm: Export ksm_madvise()
      KVM: PPC: Book3S HV: Support for running secure guests
      KVM: PPC: Book3S HV: Shared pages support for secure guests
      KVM: PPC: Book3S HV: Radix changes for secure guest
      KVM: PPC: Book3S HV: Handle memory plug/unplug to secure VM
      KVM: PPC: Book3S HV: Support reset of secure guest

Jim Mattson (1):
      kvm: vmx: Stop wasting a page for guest_msrs

Paolo Bonzini (2):
      Merge tag 'kvm-ppc-uvmem-5.5-2' of git://git.kernel.org/.../paulus/powerpc into HEAD
      KVM: x86: fix out-of-bounds write in KVM_GET_EMULATED_CPUID (CVE-2019-19332)

Peter Gonda (1):
      KVM x86: Move kvm cpuid support out of svm

Wainer dos Santos Moschetta (1):
      Documentation: kvm: Fix mention to number of ioctls classes

 Documentation/virt/kvm/api.txt              |  20 +-
 arch/powerpc/Kconfig                        |  17 +
 arch/powerpc/include/asm/hvcall.h           |   9 +
 arch/powerpc/include/asm/kvm_book3s_uvmem.h |  74 +++
 arch/powerpc/include/asm/kvm_host.h         |   6 +
 arch/powerpc/include/asm/kvm_ppc.h          |   1 +
 arch/powerpc/include/asm/ultravisor-api.h   |   6 +
 arch/powerpc/include/asm/ultravisor.h       |  36 ++
 arch/powerpc/kvm/Makefile                   |   3 +
 arch/powerpc/kvm/book3s_64_mmu_radix.c      |  25 +
 arch/powerpc/kvm/book3s_hv.c                | 143 +++++
 arch/powerpc/kvm/book3s_hv_uvmem.c          | 785 ++++++++++++++++++++++++++++
 arch/powerpc/kvm/powerpc.c                  |  12 +
 arch/x86/kvm/cpuid.c                        |  10 +-
 arch/x86/kvm/svm.c                          |   7 -
 arch/x86/kvm/vmx/vmx.c                      |  12 +-
 arch/x86/kvm/vmx/vmx.h                      |   8 +-
 include/uapi/linux/kvm.h                    |   1 +
 mm/ksm.c                                    |   1 +
 19 files changed, 1156 insertions(+), 20 deletions(-)
 create mode 100644 arch/powerpc/include/asm/kvm_book3s_uvmem.h
 create mode 100644 arch/powerpc/kvm/book3s_hv_uvmem.c
```
#### [PATCH 4.14 144/209] kvm: properly check debugfs dentry before using it
##### From: Greg Kroah-Hartman <gregkh@linuxfoundation.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Greg Kroah-Hartman <gregkh@linuxfoundation.org>
X-Patchwork-Id: 11273447
Return-Path: <SRS0=IjTT=Z2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C9948930
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Dec 2019 18:20:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A64C320862
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Dec 2019 18:20:18 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1575483618;
	bh=nQybpkEgQGYlDZRpW33M8eWJcLoJzleNnd/FTE5dnzA=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=W4ngTvuNkZJB0lekxQ35Wq0sJiwMFO08S4q/QBjCabImmgjdyGQRaAJYRRE2Br7fA
	 5vXmvFR+jqGZAaQ/pJMXocouoLtOCbC4hS7lfJFwYRsTDPvf48LIsml0ePFRelMhLm
	 HeTnY2OLpMiE3SdL4gJ8wg1nodWxlxOB7rzWiw80=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730949AbfLDSIm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 4 Dec 2019 13:08:42 -0500
Received: from mail.kernel.org ([198.145.29.99]:32878 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730941AbfLDSIk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 4 Dec 2019 13:08:40 -0500
Received: from localhost (unknown [217.68.49.72])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id B56AF20862;
        Wed,  4 Dec 2019 18:08:39 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1575482920;
        bh=nQybpkEgQGYlDZRpW33M8eWJcLoJzleNnd/FTE5dnzA=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=Y7o86Fw/MgKz1abtPdwg/FDV8A4deapwn2+KwPCLedDEowQqgtPElvovNtgH7zCa5
         umFKjFMStZPD8uINhwY+3Tiq9mHJ/eDml6qLOmlqhs97IJ44tYhD+6qtqz6NimFUJk
         083BjZrT1iky91GXtGt3xpeW8wqtCCxagyx9tb1g=
From: Greg Kroah-Hartman <gregkh@linuxfoundation.org>
To: linux-kernel@vger.kernel.org
Cc: Greg Kroah-Hartman <gregkh@linuxfoundation.org>, stable@vger.kernel.org,
 Eric Biggers <ebiggers@kernel.org>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>, kvm@vger.kernel.org,
 Paolo Bonzini <pbonzini@redhat.com>,
 Linus Torvalds <torvalds@linux-foundation.org>,
 Sasha Levin <sashal@kernel.org>,
 syzbot+7857962b4d45e602b8ad@syzkaller.appspotmail.com
Subject: [PATCH 4.14 144/209] kvm: properly check debugfs dentry before using
 it
Date: Wed,  4 Dec 2019 18:55:56 +0100
Message-Id: <20191204175333.233165534@linuxfoundation.org>
X-Mailer: git-send-email 2.24.0
In-Reply-To: <20191204175321.609072813@linuxfoundation.org>
References: <20191204175321.609072813@linuxfoundation.org>
User-Agent: quilt/0.66
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Greg Kroah-Hartman <gregkh@linuxfoundation.org>

[ Upstream commit 8ed0579c12b2fe56a1fac2f712f58fc26c1dc49b ]

debugfs can now report an error code if something went wrong instead of
just NULL.  So if the return value is to be used as a "real" dentry, it
needs to be checked if it is an error before dereferencing it.

This is now happening because of ff9fb72bc077 ("debugfs: return error
values, not NULL").  syzbot has found a way to trigger multiple debugfs
files attempting to be created, which fails, and then the error code
gets passed to dentry_path_raw() which obviously does not like it.

Reported-by: Eric Biggers <ebiggers@kernel.org>
Reported-and-tested-by: syzbot+7857962b4d45e602b8ad@syzkaller.appspotmail.com
Cc: "Radim Krčmář" <rkrcmar@redhat.com>
Cc: kvm@vger.kernel.org
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Greg Kroah-Hartman <gregkh@linuxfoundation.org>
Signed-off-by: Linus Torvalds <torvalds@linux-foundation.org>
Signed-off-by: Sasha Levin <sashal@kernel.org>
---
 virt/kvm/kvm_main.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] kvm: nVMX: VMWRITE checks VMCS-link pointer before VMCS fieldFrom: Jim Mattson <jmattson@google.com>
##### From: Jim Mattson <jmattson@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jim Mattson <jmattson@google.com>
X-Patchwork-Id: 11273645
Return-Path: <SRS0=IjTT=Z2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 556C8138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Dec 2019 21:40:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 33C572073C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Dec 2019 21:40:39 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="U9dkXQL/"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728071AbfLDVki (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 4 Dec 2019 16:40:38 -0500
Received: from mail-pj1-f73.google.com ([209.85.216.73]:47108 "EHLO
        mail-pj1-f73.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727982AbfLDVki (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 4 Dec 2019 16:40:38 -0500
Received: by mail-pj1-f73.google.com with SMTP id u6so581612pjv.14
        for <kvm@vger.kernel.org>; Wed, 04 Dec 2019 13:40:37 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=mjcK8lPLhzxkrEpDX3fdUCq0irDtJ+UuKGtrEMM0y18=;
        b=U9dkXQL/FYHvV8r9puFbhF8kHh+wFfJ0CZsq6R5AEBryGmZaEmsQwcj1nMXBoEb1YA
         l/iHJgfVK09JE49Wx78H+wLTzV2wgPOv7MSCbZcjRmJwoyo0JjgMFLTEtpJWyZm2feWq
         Izy9aCDmodC7gys/SfVSmyAGT0BydFAnEJxPy9i4NFwAqlO6hio8WsIa4vUbuJww4S4p
         xrXlteYuuHKmEaV0QIQfIhJxZRpdSuc3URzKmcoLKV5h0MkjigtfgMeG7UCLOklPazeJ
         xdo1Q8YSPlg/cLfz6DnqQ6UJ91hQHZF6AL+z5TMeF+av1fS4tOE5GQBS2vYKJ73OhDRZ
         sHEA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=mjcK8lPLhzxkrEpDX3fdUCq0irDtJ+UuKGtrEMM0y18=;
        b=AXfARloqVHlMkP76rQw03xXYN2mX7fEob2/WCnZcmVfTn8GUQeZOpfJx0GlNDXxMWx
         GOc7RVffPEBJfiiTvGgA4RD7eeWIFE+TOf7NYY/UBfN/vsi+TQsegJm+ygyS86mP4AFJ
         O9JDJ7lwCIdiodfFLVpwwrGaUYLtr0LjLhMZW0KWhplRk9CfRwwXlIWAwUs1GGChzb7b
         bcU+pJfAliW7Xbb9Jr3hmG9+CgX591yoTlhmCXrTKB99vwkCZRiYJznH6ReD8+Ffd5op
         sTAKKkfVEJCJjx5wmaTeJCruuugYVtkV0vHC1hkS9trpfa6k1Kb5YzKV2KuRFGPqydGA
         6Mdg==
X-Gm-Message-State: APjAAAVMBEs89rtE7zCvF4L2IP4dfYvn7mT3tpLNNL6F4ZFFaebIB9aT
        LdiYyclFvkfa6Hz0Rbkwake3ECT40PCFwjJnv4lSnJuJqRiOW20M8mgEDazzvI9pNLf4+vkymx3
        1N3PIV7t53jTfr//hiKxM8GKV5bjjBXiwhSKV8UZdf12+DEEA/q75RjeC5kOE4Rc=
X-Google-Smtp-Source: 
 APXvYqzm+G6CcMvWLqD1xdpShQJi1kDMbzsrDZa8KiTZGEFPrrzrC5uqirwrHlHkeD2vquQHbQTa9d7ETLOPWQ==
X-Received: by 2002:a63:ca4d:: with SMTP id o13mr5688626pgi.360.1575495637340;
 Wed, 04 Dec 2019 13:40:37 -0800 (PST)
Date: Wed,  4 Dec 2019 13:40:27 -0800
Message-Id: <20191204214027.85958-1-jmattson@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.24.0.393.g34dc348eaf-goog
Subject: [PATCH] kvm: nVMX: VMWRITE checks VMCS-link pointer before VMCS field
From: Jim Mattson <jmattson@google.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Jim Mattson <jmattson@google.com>,
        Liran Alon <liran.alon@oracle.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

According to the SDM, a VMWRITE in VMX non-root operation with an
invalid VMCS-link pointer results in VMfailInvalid before the validity
of the VMCS field in the secondary source operand is checked.

Fixes: 6d894f498f5d1 ("KVM: nVMX: vmread/vmwrite: Use shadow vmcs12 if running L2")
Signed-off-by: Jim Mattson <jmattson@google.com>
Cc: Liran Alon <liran.alon@oracle.com>
---
 arch/x86/kvm/vmx/nested.c | 38 +++++++++++++++++++-------------------
 1 file changed, 19 insertions(+), 19 deletions(-)

```
#### [PATCH v5 1/6] KVM: X86: Fix kvm_bitmap_or_dest_vcpus() to use irq shorthand
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11273473
Return-Path: <SRS0=IjTT=Z2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 02D076C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Dec 2019 19:07:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D422620803
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Dec 2019 19:07:55 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Xa4l98rX"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728845AbfLDTHz (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 4 Dec 2019 14:07:55 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:22921 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1728465AbfLDTHb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 4 Dec 2019 14:07:31 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1575486450;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=kn/llSEPws9Kaihse6HkAcboPO6kvjhOBVqBu50kJWM=;
        b=Xa4l98rXBnGh+ETCe0JsN0hNfWFnevNFNopEHcMO5FXqk7R63sKowkrOsuC8BBkEKGbRFz
        sLk/y4Pc0NnvIGLhvVV0tNG0MoNm5xUwbdxCgyKqc+myTYujLjwP/yQlRvZy/S6sTP5Gr2
        oqJ9wh5O1E068gIUf+sHP/pxh+Rr3F8=
Received: from mail-qv1-f71.google.com (mail-qv1-f71.google.com
 [209.85.219.71]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-31-GoAYR2thN3OqKKq4YoRjjQ-1; Wed, 04 Dec 2019 14:07:25 -0500
Received: by mail-qv1-f71.google.com with SMTP id m43so456585qvc.17
        for <kvm@vger.kernel.org>; Wed, 04 Dec 2019 11:07:25 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=qDMFszQpTCz8aKUy2p2BRtrOo8b1SfrY7qPPp6I+jnk=;
        b=qkCqBXhWxRg4ZYk+lHtKleZ3fAY86tuHPIQ7imzKXYDM8I9TvuQzpi4XMUcJGjd14m
         7uQ71HNXtaKbgdH2KMLNJkug4VO+zWVY9xpNuVJNoiPr/EUWKMmS7vQtYJ3NSFfes1Xe
         +yFDxczvfPt8B4hDNa91u/lKAF9FQ5vmi2mgSeXWauDP49QvHfIUxpGdqeiQbQnW56C8
         5iXWlph8O3Q/xxNB7TAvYlIDOs2KBZiTsGEOxFxSWT1Jhrfd/mqfdFrZ6sSS0uYVSq5c
         0ejrwpZ6Jahwo5ien0gK3JN4M1QhY9ZFrCbbSTzuIZp2tutYGsBIpva8uytISVH7GlkL
         03Tw==
X-Gm-Message-State: APjAAAWUzQpJ3fIYcqJ4JXE0t6SKVCaDB8dh8dG0QHCRyU+Gk5yK9nmX
        GRXcwuz617FOdiPnzJ6HEmrIvV2KlduKY/fcU3Flakx+ZcIo9aZi8Xk3olFYbCukZ6GIUKmvUa9
        pWFMTdS1rQCep
X-Received: by 2002:a37:f605:: with SMTP id y5mr4645601qkj.59.1575486444772;
        Wed, 04 Dec 2019 11:07:24 -0800 (PST)
X-Google-Smtp-Source: 
 APXvYqwXcJerAYwuG8Nz4ZOyamZB1Cf11CnFdKyqm2/DvrswGbmWblNXhZd72Q8pcAs4X10qlKVa5A==
X-Received: by 2002:a37:f605:: with SMTP id y5mr4645584qkj.59.1575486444531;
        Wed, 04 Dec 2019 11:07:24 -0800 (PST)
Received: from xz-x1.yyz.redhat.com ([104.156.64.74])
        by smtp.gmail.com with ESMTPSA id
 y18sm4072126qtn.11.2019.12.04.11.07.23
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 04 Dec 2019 11:07:23 -0800 (PST)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Nitesh Narayan Lal <nitesh@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        peterx@redhat.com, Vitaly Kuznetsov <vkuznets@redhat.com>
Subject: [PATCH v5 1/6] KVM: X86: Fix kvm_bitmap_or_dest_vcpus() to use irq
 shorthand
Date: Wed,  4 Dec 2019 14:07:16 -0500
Message-Id: <20191204190721.29480-2-peterx@redhat.com>
X-Mailer: git-send-email 2.21.0
In-Reply-To: <20191204190721.29480-1-peterx@redhat.com>
References: <20191204190721.29480-1-peterx@redhat.com>
MIME-Version: 1.0
X-MC-Unique: GoAYR2thN3OqKKq4YoRjjQ-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The 3rd parameter of kvm_apic_match_dest() is the irq shorthand,
rather than the irq delivery mode.

Fixes: 7ee30bc132c6 ("KVM: x86: deliver KVM IOAPIC scan request to target vCPUs")
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Peter Xu <peterx@redhat.com>
---
 arch/x86/kvm/lapic.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: x86: fix out-of-bounds write in KVM_GET_EMULATED_CPUID (CVE-2019-19332)
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11272759
Return-Path: <SRS0=IjTT=Z2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4880D13A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Dec 2019 11:20:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2360020833
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Dec 2019 11:20:26 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="pHnQ75nq"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727638AbfLDLUS (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 4 Dec 2019 06:20:18 -0500
Received: from mail-wm1-f65.google.com ([209.85.128.65]:34650 "EHLO
        mail-wm1-f65.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727577AbfLDLUS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 4 Dec 2019 06:20:18 -0500
Received: by mail-wm1-f65.google.com with SMTP id f4so4599045wmj.1;
        Wed, 04 Dec 2019 03:20:16 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=H33X4AK+u43gUnhB1O2fMOEJjx19wp0DYd+Rf48fRQA=;
        b=pHnQ75nqMQUj1Idg8y+ZdY1KcmPx6nqGQxnOGR/QcMRyLiHYKfdEj1ke5yQ/IkLbDT
         dFBvQrbFgk5v0GajNDVSsYtO5oKaW2cSVSQ/GyKBYp/raOWVXQqB2NPPkWJa86xd/L1h
         2ex+i7D9+VKq+7dyCFQMDECnwxYMePPLth2iJZfR9dZ09v8XZFtmuEIZqHBsuxZd5Xhh
         ZPicdGxQmS6b+47dkvCkBOItW6o9Zdps+snIQsyWqOk2lUFNSEkxKFxCus4PeM+zG4gr
         SpjON49YzWFFzNetDesRpBFwWioDykVupisiI0w2WSHUZWEGPdKi4gKMT/IjP29WsHWv
         qPew==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=H33X4AK+u43gUnhB1O2fMOEJjx19wp0DYd+Rf48fRQA=;
        b=hO2JJJrIMEwM7k1lsqng4oCHR/bKP4in9ahbTMTFycdeE0MPrrlefqZEwm6HAEmp7L
         8T9fms70s8uWryd13yl5+ydMq3kFQyygw2OW1UAOkoVJYl79EcLuIYr2WvBTF7dR77U+
         8udoGeoR5DeTWWNG3FGspLDxc8hyfkkP4H7iffi0O+EF+sPjqyB/Hd3R20SZ1FQr6wOX
         huL/nHpuNrAq7o7zf5ZnwIg1puTSyPR6t2f+0zck3qtkQRmMoUE6s8As3nL2Y8ArfMv4
         7NlFSvvJbmqCDvE7H/HukONK+rhT+WCdscJ6opj6YiVK01xXN20r9YWuMTKQvhoChj+d
         3pkQ==
X-Gm-Message-State: APjAAAXbhemyRiYSXwnvZ8TrasV/hIPnnuVcaLW0pxV6rYaLJPbtrCRn
        BAeh+phKJw+dV4diq5i0OB53xRt5
X-Google-Smtp-Source: 
 APXvYqx3sfx7h6wlSw+Zba7Lzr+rEDFkJ3LR55qcg6m9TLRL50Y7jecyIWXGAsuY7uEkIcwsZvWnkg==
X-Received: by 2002:a7b:ce19:: with SMTP id m25mr20006752wmc.6.1575458415389;
        Wed, 04 Dec 2019 03:20:15 -0800 (PST)
Received: from 640k.lan ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 z13sm6595440wmi.18.2019.12.04.03.20.13
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Wed, 04 Dec 2019 03:20:14 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: bp@alien8.de
Subject: [PATCH] KVM: x86: fix out-of-bounds write in KVM_GET_EMULATED_CPUID
 (CVE-2019-19332)
Date: Wed,  4 Dec 2019 12:20:12 +0100
Message-Id: <1575458412-10241-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The bounds check was present in KVM_GET_SUPPORTED_CPUID but not
KVM_GET_EMULATED_CPUID.

Reported-by: syzbot+e3f4897236c4eeb8af4f@syzkaller.appspotmail.com
Fixes: 84cffe499b94 ("kvm: Emulate MOVBE", 2013-10-29)
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/cpuid.c | 5 ++++-
 1 file changed, 4 insertions(+), 1 deletion(-)

```
#### [PATCH] KVM: x86: use CPUID to locate host page table reserved bits
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11273027
Return-Path: <SRS0=IjTT=Z2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3F11E930
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Dec 2019 14:51:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1E1C62081B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Dec 2019 14:51:09 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="k49RhWK/"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728060AbfLDOvF (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 4 Dec 2019 09:51:05 -0500
Received: from mail-wr1-f65.google.com ([209.85.221.65]:33456 "EHLO
        mail-wr1-f65.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727850AbfLDOvE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 4 Dec 2019 09:51:04 -0500
Received: by mail-wr1-f65.google.com with SMTP id b6so9011254wrq.0;
        Wed, 04 Dec 2019 06:51:03 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=yYZqbXXZPzEVcnnLng9M3IBm2A+jek74weSxMJq/iFE=;
        b=k49RhWK/OQMSeTLWRRb/52BYdCf1Q/03pZKLEloGnJ7ddXIOfJiz/6JfpuiJVbPGjX
         gXMY6YTd/Qqw9UFEkw+9KUI5Vp0ng/hZ66lLnfe9zWFt0aVpiUS92CPDQKMpI+M6wVwR
         e2CaDlPKATJbUVes/UpFot8+PpD2QgP4AGEd/HZpSQJ8Ot80iazLwIid2ITtch00e8XY
         D8uVwpk5iITo54/nARn5hQ0YbV3h+ODJmXkOuvJGVHt/jmJBgQXM5mmhQtn3dDK7ew/N
         fMyS36e01rxhWkCmWR8mrpWKFdH7wdut7+zK/Kw88uwBNCRFT1Y/ccy8pfBSBjg/+wu5
         bbTw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=yYZqbXXZPzEVcnnLng9M3IBm2A+jek74weSxMJq/iFE=;
        b=OOo+9RfGlsXKw2qVpt7FGCg+QsbMWf7YyU0rNfovUQZFpOmcG6URGc9fwcLMCFZbO6
         Yl2YOX5OGyptkL0rUhypnM7X3Aq1fRMcAUe/w2hziwyLuUnjYQ2S9H5WpnlEmxxGDLPk
         DQjkOzfLD4aXabLMCEGEUSgo1JaU5712Kol76s+X8oXN+Bjynk252bn3jntKTqqyQC1u
         xjgbMp1t5XZDtAk+mZNVmqDyNEuj0RkThJML20Tq2gRnPYJvp/1ua+ghJFJmNQpOhIRq
         KMIETN1NUhLyKcp8eUjxE+mCX9YvwNDtA2RjA6OSMU16Kv7G0aOse2CyqvO2Ibsab/O8
         XwyQ==
X-Gm-Message-State: APjAAAUMSrVNJ+wnWoGND9TIw1SMf8z3TWaAqog3W6ilp9FHWvw4AN8e
        +47dOQSDx+z5jhYE2/RK1B5NA8dU
X-Google-Smtp-Source: 
 APXvYqzhNhpH8GkpLpuDoFIfARsuUlf8LRkpE+8kJfbaaR4NmRo7TS5sSDxQ0Hyau5wcWOxyLFSfnw==
X-Received: by 2002:adf:ec48:: with SMTP id w8mr4606345wrn.19.1575471062187;
        Wed, 04 Dec 2019 06:51:02 -0800 (PST)
Received: from 640k.lan ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 g74sm6747674wme.5.2019.12.04.06.51.01
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Wed, 04 Dec 2019 06:51:01 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: stable@vger.kernel.org
Subject: [PATCH] KVM: x86: use CPUID to locate host page table reserved bits
Date: Wed,  4 Dec 2019 15:51:00 +0100
Message-Id: <1575471060-55790-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The comment in kvm_get_shadow_phys_bits refers to MKTME, but the same is actually
true of SME and SEV.  Just use CPUID[0x8000_0008].EAX[7:0] unconditionally, it is
simplest and works even if memory is not encrypted.

Cc: stable@vger.kernel.org
Reported-by: Tom Lendacky <thomas.lendacky@amd.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/mmu/mmu.c | 12 ++++--------
 1 file changed, 4 insertions(+), 8 deletions(-)

```
#### [PATCH] MAINTAINERS: remove Radim from KVM maintainers
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11273015
Return-Path: <SRS0=IjTT=Z2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 50650930
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Dec 2019 14:33:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2ECB52077B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Dec 2019 14:33:43 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="OEKH0QMw"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728031AbfLDOdk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 4 Dec 2019 09:33:40 -0500
Received: from mail-wm1-f65.google.com ([209.85.128.65]:39801 "EHLO
        mail-wm1-f65.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727887AbfLDOdj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 4 Dec 2019 09:33:39 -0500
Received: by mail-wm1-f65.google.com with SMTP id s14so8161421wmh.4;
        Wed, 04 Dec 2019 06:33:38 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=lzBlgZY8Eh46qsnlMJQl2UIjKvxdbeDw64m/NdYI+9g=;
        b=OEKH0QMwb4VBZufUS19qcCqQT5bhHUWA3JZf660ysP2uXnElhv/3IpQvE9YdJpYr6M
         iMoFvO8lSZA33K8kjy0/fcgFD8boDWBcw0wyH0eyuAkhvO7BwNsMq9K+LJ6JlgOTRnku
         92JvdAh6PeAr6I8eMD6keN45wDR9f92VnluEZk2Lm5zhcrtRzXa54HNIjZMS1t5vwgQc
         uXDRyoy9BaUI0raUSF1ySVcg6q6Hu0DNt5Jm0c2P3m1as2cTf9s94/f3JvGlow0iUuyK
         iGb0a0bUj+CeV+TVvBCsYHb8CvvQqQ0/lswNtBH8pmajFifqCw5Y0vGznpK4AftAl9OA
         h1pg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:subject:date:message-id
         :mime-version:content-transfer-encoding;
        bh=lzBlgZY8Eh46qsnlMJQl2UIjKvxdbeDw64m/NdYI+9g=;
        b=DVqKf2ERxAGhZjWPz3VZQMXBEN90MNs9z0jLYRsMcKePmF6lknH/4idy0AidIbpsBT
         StI31ah1PaN9ceDv9Rx36YXMF+W7TzndI44OIlehreXN9kDaQu5XN58LWs+IFpYvsjiV
         /iDTruujaiZoHu+BAVd7/ojyU2T/wJ+69vE+AmOQo4miesx0ZW6jXilgr2nsIw3kZhpO
         KEZBdQBRIOo8X1UTJq4cBssjlweuKef+f8lSz4EgMvz9n/piER4dJ3cLJSrnVRxSFytu
         X7wm2+V0JE7GMUdn7P50+z5Ds2b9W7V+VXnkJ/6u47EEWcZq1goIr61R9An4PoRXHl/j
         BPRg==
X-Gm-Message-State: APjAAAUxEdAPqyXIjyp1h9W34cMzuLKvWMfr73qtvCPdoMoS/oaIQcYZ
        wNsVjzB8m0ldTiIj1pqMooNgJtom
X-Google-Smtp-Source: 
 APXvYqwi8xQUPMu8oCE9IIOZwcO4pLfcCFfRmNRvfKsHgTLAGmnkldXlwqiIEdVpO3y2IuAQLrbz/Q==
X-Received: by 2002:a1c:a70e:: with SMTP id
 q14mr15775757wme.142.1575470017470;
        Wed, 04 Dec 2019 06:33:37 -0800 (PST)
Received: from donizetti.redhat.com ([2001:b07:6468:f312:8dc6:5dd5:2c0a:6a9a])
        by smtp.gmail.com with ESMTPSA id
 m3sm8278047wrs.53.2019.12.04.06.33.36
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 04 Dec 2019 06:33:36 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [PATCH] MAINTAINERS: remove Radim from KVM maintainers
Date: Wed,  4 Dec 2019 15:33:35 +0100
Message-Id: <20191204143335.14168-1-pbonzini@redhat.com>
X-Mailer: git-send-email 2.21.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Radim's kernel.org email is bouncing, which I take as a signal that
he is not really able to deal with KVM at this time.  Make MAINTAINERS
match the effective value of KVM's bus factor.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 MAINTAINERS | 2 --
 1 file changed, 2 deletions(-)

```
#### [PATCH] target/i386: relax assert when old host kernels don't include msrs
##### From: Catherine Ho <catherine.hecx@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Catherine Ho <catherine.hecx@gmail.com>
X-Patchwork-Id: 11272485
Return-Path: <SRS0=IjTT=Z2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 13254109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Dec 2019 08:52:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E0FC520675
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Dec 2019 08:52:21 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="pxvE9MO5"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726893AbfLDIwU (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 4 Dec 2019 03:52:20 -0500
Received: from mail-qt1-f196.google.com ([209.85.160.196]:45752 "EHLO
        mail-qt1-f196.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725830AbfLDIwU (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 4 Dec 2019 03:52:20 -0500
Received: by mail-qt1-f196.google.com with SMTP id p5so6911571qtq.12
        for <kvm@vger.kernel.org>; Wed, 04 Dec 2019 00:52:20 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=EOhS8JDsg867aMPTPPeteOvbmqqjsw5vk6vXxMRaXi4=;
        b=pxvE9MO5f9p/yUNdCgDLZQPjNTm3GpliVlCjX11Hc+NODaKH6B35Fyscwpgn+cqcL7
         zgpfCuNw51xheY4xzL8Y/cgbvP6WlKdZaPbxpSYadkpH0eOPZyVMUet8SINxpFRAT5C5
         8j1P+Zuhjznd1SmYvp+uwrQ1JYs6dhjkzGCBzq9SbfWoGrSeZbbJrHDRuqLjtbZMrLtJ
         qkg6dWhdASyMNvhH2pr3ApZYbmEXt5U2Zn/8K3L2ljh7h/hrcc0+R+vHa0C7+5xaH6LU
         AM5skbDP2Holn90xSPgdwTNonumP/m7RHu92H28cMcYVjPihj0ltD2J+iW6sO6ZjRqWP
         MQKQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=EOhS8JDsg867aMPTPPeteOvbmqqjsw5vk6vXxMRaXi4=;
        b=XNt3ch2fqnnsaUYjCOzPQR2xi4x47DrgGBwmPiEj6idkZ46aij0mao3Mwr0U8QwhEA
         i6nx8k+343ouOjbfstZW4osqlgfP4JByeBlM2Wd/mJqH/oqxr0QSQj+d6QCYMAYhmqXT
         ppnXyA25Cdxrf3TOyCG5U+dk5YmqKrNrwzJRPEiQTCCMWlpm+cYB1WpXKyuleKOnZ9fb
         Zn6jaPj/tPO6oO07p7Vb05K0Jf1L8G8vDWOMtE9zpd/VmdHsFXXkQEr65lhjy+1h4kzn
         y+5L93AJAc4hqoaidkjq3rYbpreStdmZzQzymKfLq6PilKmx5+pM6RNujB3d8xqNFSzC
         Royw==
X-Gm-Message-State: APjAAAXPJbetp7N+jkamEwHn5Ru/ifBfxTadYw7G7n78tjtdQEomxDhU
        ylWsm+1o3QzhfUez+mY32Io=
X-Google-Smtp-Source: 
 APXvYqzTEn4f5QtgZACc5msyimnIHXttn0a0OY37DJuQ0hHUQX9gHuGApLqlXXYZrGFZEr/p65/7TQ==
X-Received: by 2002:ac8:23a5:: with SMTP id q34mr1570560qtq.83.1575449539835;
        Wed, 04 Dec 2019 00:52:19 -0800 (PST)
Received: from host.localdomain (104.129.187.94.16clouds.com.
 [104.129.187.94])
        by smtp.gmail.com with ESMTPSA id
 q187sm3351795qkd.92.2019.12.04.00.52.19
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Wed, 04 Dec 2019 00:52:19 -0800 (PST)
From: Catherine Ho <catherine.hecx@gmail.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Marcelo Tosatti <mtosatti@redhat.com>, qemu-devel@nongnu.org
Cc: Richard Henderson <rth@twiddle.net>,
        Eduardo Habkost <ehabkost@redhat.com>, kvm@vger.kernel.org,
        Catherine Ho <catherine.hecx@gmail.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Subject: [PATCH] target/i386: relax assert when old host kernels don't include
 msrs
Date: Wed,  4 Dec 2019 03:50:30 -0500
Message-Id: <1575449430-23366-1-git-send-email-catherine.hecx@gmail.com>
X-Mailer: git-send-email 1.7.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit 20a78b02d315 ("target/i386: add VMX features") unconditionally
add vmx msr entry although older host kernels don't include them.

But old host kernel + newest qemu will cause a qemu crash as follows:
qemu-system-x86_64: error: failed to set MSR 0x480 to 0x0
target/i386/kvm.c:2932: kvm_put_msrs: Assertion `ret ==
cpu->kvm_msr_buf->nmsrs' failed.

This fixes it by relaxing the condition.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Catherine Ho <catherine.hecx@gmail.com>
---
 target/i386/kvm.c |    2 +-
 1 files changed, 1 insertions(+), 1 deletions(-)

```
#### [PATCH v2] kvm: vmx: Stop wasting a page for guest_msrsFrom: Jim Mattson <jmattson@google.com>
##### From: Jim Mattson <jmattson@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jim Mattson <jmattson@google.com>
X-Patchwork-Id: 11271987
Return-Path: <SRS0=IjTT=Z2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8118A138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Dec 2019 00:25:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 59993206E4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Dec 2019 00:25:17 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="tT/Rr/kx"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726060AbfLDAYx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 3 Dec 2019 19:24:53 -0500
Received: from mail-pl1-f201.google.com ([209.85.214.201]:50795 "EHLO
        mail-pl1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726008AbfLDAYx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 3 Dec 2019 19:24:53 -0500
Received: by mail-pl1-f201.google.com with SMTP id c18so2592105plo.17
        for <kvm@vger.kernel.org>; Tue, 03 Dec 2019 16:24:53 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=XK0YqNOqBf++GW8F+qSvBh8TlM8iwDKRqB87FNLDCgc=;
        b=tT/Rr/kx2NL+uP/dyMOEO4OkQHXc9vjgXyZcicRSdOUtcdV/73ldlf8aY6lte6i/bb
         KRf3u2MinFH+v3H+jGztK51Od+CxT0PfLNUZnRRFDKv/Qs3unSs19EAohp0f/KCAKE74
         EfBPj/WmQ4/o0gSDUtKUiQHMhI/TN992+Z1vDxmNJRLGBd6kiGWXCoWpQhPGoBWpbzaq
         1EZHAQJEXueQy7kOJKdGAYOjv9oE626KyTkeG6fVSpSo5hSUiG0JcXK4fji+RPFl7NIT
         g2L2Edet2dSmOzSAJ/JIsx2/1BiJXJg4d8yNusg93GzY7rzXb7yOt5yclP8B4kHqDSp0
         BlGA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=XK0YqNOqBf++GW8F+qSvBh8TlM8iwDKRqB87FNLDCgc=;
        b=FBJnWjYRVY8vAj3Mh2c6nfpkT3PQCGPm5IWmcTjb3GZQ/PTuSHCrSDYU+6muovsEwE
         PMA0XnNqFHHyIP4fImu2CM2QC2CuyMUPG6wLmWNf8w9gwryGYKqnB2RLfXzikfreDbjk
         IrP2bchuvGUAQz//9ZpfyVnX0LsybW9sddFXUS2pD4orYNre+904KtbZpKsYeAMza767
         Eu9FiCm6x0BwEb2//CwyAQyZ71zmYV1XYeg9Patz/f8sldezBq9UiknG4FDcm1PiPyMz
         4PECsAFRZycu/t3WnNeYDDNE7kzCoZEp7W+p8/mWB/9s1o7lJgoPQUznkmTjfY0SjM4x
         Uyng==
X-Gm-Message-State: APjAAAW2lwBXyzncmSh4UTsE8UHXKdmTobZZFlGly04zXp2Jkqril2Jp
        /t6wYuTHWOppvphW1cofLKraNrpAmTJHAVGa6ClqNO1iZQqy+aC8pE2O5uQ7Wbl64Pn8UVvVyNc
        bxq1bDIGobvFd1PsYg7mNc4FqZ+KqxXDqYz77w8216ahTyTZ3/K0V/+2mgN/h48k=
X-Google-Smtp-Source: 
 APXvYqymFATEUdEorat4ogLD0EWFv2FYNhX+bHfY/3gn+xxCEeG91yQNlwKI8Z83Vg6OslGl7MfjCBeg3fMKMw==
X-Received: by 2002:a63:de08:: with SMTP id f8mr466986pgg.107.1575419092432;
 Tue, 03 Dec 2019 16:24:52 -0800 (PST)
Date: Tue,  3 Dec 2019 16:24:42 -0800
Message-Id: <20191204002442.186018-1-jmattson@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.24.0.393.g34dc348eaf-goog
Subject: [PATCH v2] kvm: vmx: Stop wasting a page for guest_msrs
From: Jim Mattson <jmattson@google.com>
To: kvm@vger.kernel.org,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Cc: Jim Mattson <jmattson@google.com>,
        Liran Alon <liran.alon@oracle.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We will never need more guest_msrs than there are indices in
vmx_msr_index. Thus, at present, the guest_msrs array will not exceed
168 bytes.

Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
---
v1 -> v2:
  Changed NR_GUEST_MSRS to NR_SHARED_MSRS.
  Added BUILD_BUG_ON(ARRAY_SIZE(vmx_msr_index) != NR_SHARED_MSRS).

 arch/x86/kvm/vmx/vmx.c | 12 ++----------
 arch/x86/kvm/vmx/vmx.h |  8 +++++++-
 2 files changed, 9 insertions(+), 11 deletions(-)

```
#### [PATCH v2] KVM: x86: use CPUID to locate host page table reserved bits
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11273121
Return-Path: <SRS0=IjTT=Z2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 03F1213A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Dec 2019 15:40:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CF9062084F
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  4 Dec 2019 15:40:52 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="LkEmcI4T"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728570AbfLDPkt (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 4 Dec 2019 10:40:49 -0500
Received: from mail-wr1-f68.google.com ([209.85.221.68]:42430 "EHLO
        mail-wr1-f68.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728357AbfLDPkl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 4 Dec 2019 10:40:41 -0500
Received: by mail-wr1-f68.google.com with SMTP id a15so9144050wrf.9;
        Wed, 04 Dec 2019 07:40:40 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=3CWC98h+5raJqQO+ka9hGiDloggJe6dDITvR1rS981E=;
        b=LkEmcI4TGNSbygcJ7Cko+s9jE4BlWzkAAeKiWUTHaBfr1yAo7wjnpKwN1v9UuMx65t
         pVyFemQvkAQP4sTma62IrTHQJ7WI6CHPm+t8RcqfXnJ+Edn+3dAu6Ay138Uq+Nd+BG8W
         7F+vqfv2mPGubnmF3tOpfnqMAxKjleNr67b4Y2neErbm/mGF4i4RitGjxfgNhn/cZOIL
         zKT/Uk9ijI5xzkpnLzA0o6iXP0ECKT4myNr9sII/seqoKUdblE2IyonZ8c1j72peaK5I
         RB6Ih+LIi+kJiwXcwP4pgSCroZKNZGxPGP6yU8fAj0vW54DCYUInhLM7NL1c3eEfJZEe
         SXvA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=3CWC98h+5raJqQO+ka9hGiDloggJe6dDITvR1rS981E=;
        b=G71MsSE1Kf4zhZRgrYj1D5afo77NuagSHrufcg+dxhsVt4IQBlpmclsMQCvsR+/sbn
         nLE3vxtDdgaHzuOmfnhgBV1lafXTygDXPoTsPo8hB6xa4uOxr3T4N67moT48MczYi0SL
         8E1ii1MZrAyApvLfYIXHd5Wxe2i9yVc0+5+F7yos48aQ+BGcKx9aFk2BmnTwdngF2v5L
         BIfUljgtGr2Ij413xipgasS9OEySMNH3RL+grbg14lrsQJJhdg1M07dgN2Xa5DCpFlOb
         Gd3kpgtpm/AEnPxDM192h5FI5erqBZN+LgSuDS2ix3dCTrgn9RGKUxtEe1Dt7i56Asae
         Ubpg==
X-Gm-Message-State: APjAAAV4b7fkitg52YnUMkMRaLEGBW8/gMyhcMu13XWXmua8RMM7AM1H
        c97RwdYhUKjmK88oRSLxENnm2brc
X-Google-Smtp-Source: 
 APXvYqzZo5rJU83WbGx4l8YKrQdA+4qX4BShmaAoOAj76qDv2/BdhY3tSWVbfAfWwkcKl922ZsNHhQ==
X-Received: by 2002:adf:dd52:: with SMTP id u18mr4805400wrm.131.1575474038983;
        Wed, 04 Dec 2019 07:40:38 -0800 (PST)
Received: from 640k.lan ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 d19sm2372235wmd.38.2019.12.04.07.40.38
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Wed, 04 Dec 2019 07:40:38 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: thomas.lendacky@amd.com, sean.j.christopherson@intel.com,
        stable@vger.kernel.org
Subject: [PATCH v2] KVM: x86: use CPUID to locate host page table reserved
 bits
Date: Wed,  4 Dec 2019 16:40:37 +0100
Message-Id: <1575474037-7903-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The comment in kvm_get_shadow_phys_bits refers to MKTME, but the same is actually
true of SME and SEV.  Just use CPUID[0x8000_0008].EAX[7:0] unconditionally if
available, it is simplest and works even if memory is not encrypted.

Cc: stable@vger.kernel.org
Reported-by: Tom Lendacky <thomas.lendacky@amd.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/mmu/mmu.c | 20 ++++++++++++--------
 1 file changed, 12 insertions(+), 8 deletions(-)

```
