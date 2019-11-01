#### [GIT PULL] KVM patches for Linux 5.4-rc6
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11222029
Return-Path: <SRS0=FBlN=YY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CCA9C13BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 31 Oct 2019 22:53:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A8E0D216F4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 31 Oct 2019 22:53:52 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="DdnQ2aG4"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728235AbfJaWxs (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 31 Oct 2019 18:53:48 -0400
Received: from mail-wr1-f66.google.com ([209.85.221.66]:42514 "EHLO
        mail-wr1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726540AbfJaWxs (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 31 Oct 2019 18:53:48 -0400
Received: by mail-wr1-f66.google.com with SMTP id a15so7975829wrf.9;
        Thu, 31 Oct 2019 15:53:46 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=sAzljLRgSt0T4SkgYsaqgvjH5/V1zSYWw1k97qxMfJk=;
        b=DdnQ2aG41QAJSboenV4wySHF2meXgLSRA649oxBw9RAPNghNJEHSiFM5YwuLI8CfeO
         df5hfVi+DcA4OKQihRG6s5omuAbGxCR0URTee3j4Jg12CTsH/YdWWd+nh2eUmUXZYFXL
         CcDRMGPtcCa527wuEKWJ8tCjBX10DrMrAplEzF4N9JEKS0LniqTiIhNfm4KwTjO+FUB+
         dTi6qDoHGsoHcK+UJY2SyU72bOIWNXelJKWzO+O3toJQGOrHGTWBXGShL1gF2MXio8Xn
         EcPWDxo/sH4akb07nPs+3Q9KmL/TK6/eZjMMROlvPWUgs3g/cp9L4UQZSL+Co8p5yLMq
         RcQw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :mime-version:content-transfer-encoding;
        bh=sAzljLRgSt0T4SkgYsaqgvjH5/V1zSYWw1k97qxMfJk=;
        b=cov24UiiLokjumC/QDmFykp3+YctReUcRoRhE+53gswRffYZBnvqScKwv29rYCUCLj
         SSM2hReK+l0HcdqDzx4MIAwRxXlz0hagwHdeVcwuw/0+wWgw9uewtQzfvSkWbflVOdCX
         KDOucDjJOwGaF2fDfn+s2BEJu+JPKD78qPmHIuhusZNuGjuSp3GHbs4V5va8ViZD9dQw
         aYF/CWao0ueujQzZkm+0Yvgc6MofkGe9XlPqFEOLyQU2x2TaPZAUnATt4KurepaM6m7h
         2o1uDLuTSXRNnSVt+KaeMdFS/fMnIeDRz0YeFh79NmFowWcYysnzQPvut9NG/OrcU+Cq
         3kbQ==
X-Gm-Message-State: APjAAAWcGJLz4nOg/SsQ4Kt8+ui4zVSAOkzPH0f6JkGY6t7kLBWjD3+2
        DMjCWvf9y+sPsH3xB0qZBAuyTd2OZQo=
X-Google-Smtp-Source: 
 APXvYqz1p8qVO3J188bjhlrVa1hJ4uYvoW5VQM0J2M2QgJVLMiEUUEHEjKw1yL5l5r9CQzgCBegF9A==
X-Received: by 2002:a5d:6448:: with SMTP id d8mr5306172wrw.88.1572562425910;
        Thu, 31 Oct 2019 15:53:45 -0700 (PDT)
Received: from donizetti.redhat.com (94.222.26.109.rev.sfr.net.
 [109.26.222.94])
        by smtp.gmail.com with ESMTPSA id
 l4sm4673235wml.33.2019.10.31.15.53.44
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 31 Oct 2019 15:53:44 -0700 (PDT)
From: Paolo Bonzini <pbonzini@redhat.com>
To: torvalds@linux-foundation.org
Cc: linux-kernel@vger.kernel.org, rkrcmar@kernel.org,
        kvm@vger.kernel.org
Subject: [GIT PULL] KVM patches for Linux 5.4-rc6
Date: Thu, 31 Oct 2019 23:53:47 +0100
Message-Id: <20191031225347.26587-1-pbonzini@redhat.com>
X-Mailer: git-send-email 2.21.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linus,

The following changes since commit 671ddc700fd08b94967b1e2a937020e30c838609:

  KVM: nVMX: Don't leak L1 MMIO regions to L2 (2019-10-22 19:04:40 +0200)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to 9167ab79936206118cc60e47dcb926c3489f3bd5:

  KVM: vmx, svm: always run with EFER.NXE=1 when shadow paging is active (2019-10-31 12:13:44 +0100)

----------------------------------------------------------------
Generic: fix memory leak failure to create VM.
x86: fix MMU corner case with AMD nested paging disabled.

----------------------------------------------------------------
Jim Mattson (2):
      kvm: Allocate memslots and buses before calling kvm_arch_init_vm
      kvm: call kvm_arch_destroy_vm if vm creation fails

Paolo Bonzini (1):
      KVM: vmx, svm: always run with EFER.NXE=1 when shadow paging is active

 arch/x86/kvm/svm.c     | 10 ++++++++--
 arch/x86/kvm/vmx/vmx.c | 14 +++-----------
 virt/kvm/kvm_main.c    | 48 ++++++++++++++++++++++++++----------------------
 3 files changed, 37 insertions(+), 35 deletions(-)
```
#### [GIT PULL] Please pull my kvm-ppc-next-5.5-1 tag
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paul Mackerras <paulus@ozlabs.org>
X-Patchwork-Id: 11221021
Return-Path: <SRS0=FBlN=YY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1E5AE14DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 31 Oct 2019 11:14:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id F04BE208C0
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 31 Oct 2019 11:14:15 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ozlabs.org header.i=@ozlabs.org
 header.b="nWkaP5ya"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727286AbfJaLOP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 31 Oct 2019 07:14:15 -0400
Received: from bilbo.ozlabs.org ([203.11.71.1]:48755 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726722AbfJaLOP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 31 Oct 2019 07:14:15 -0400
Received: by ozlabs.org (Postfix, from userid 1003)
        id 473jPv2Vmzz9sPJ; Thu, 31 Oct 2019 22:14:11 +1100 (AEDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=ozlabs.org; s=201707;
        t=1572520451; bh=YPLeyvpRHfFhn4xyIHHwVnQ9E5S2/47CprDiBRowXkc=;
        h=Date:From:To:Cc:Subject:From;
        b=nWkaP5yaFuxj4hVYUWCGMFmI9ATh4mIakiiEHPuzlbkxPMUOWMbqCX3lqH/7mvh+m
         9ivIfNAiUByM1yyz1fm9LDNjbblApMYx4xCbpGraiq/QQ4Yr2mjjQerVUtteuGUfjd
         H5bKET4cWLIZ6GJ4twKiLPt0y68rJ2mYyt9xqAHyQxOS/Cz3kXNw8rbj2mc+DtnPm7
         /RrZidpuX7dw766e3mGNpLh6Ngwu8AKONAspg1Kq+RwzKP2xQ/ISHx3RBuul8ukg1d
         4rK4cmR5G5KE2wxXPADBKmKmOCSqM7QTqrCVBe8KXBCRWosOQy/+CStWOkSRYTyXSE
         eWI3dbVBgBD3A==
Date: Thu, 31 Oct 2019 12:13:49 +0100
From: Paul Mackerras <paulus@ozlabs.org>
To: Paolo Bonzini <pbonzini@redhat.com>,
 Radim =?utf-8?b?S3LEjW3DocWZ?= <rkrcmar@redhat.com>, kvm@vger.kernel.org
Cc: kvm-ppc@vger.kernel.org
Subject: [GIT PULL] Please pull my kvm-ppc-next-5.5-1 tag
Message-ID: <20191031111349.GA8045@blackberry>
MIME-Version: 1.0
Content-Disposition: inline
User-Agent: Mutt/1.5.24 (2015-08-30)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Paolo or Radim,

Please do a pull from my kvm-ppc-next-5.5-1 tag to get a PPC KVM
update for v5.5.

Thanks,
Paul.

The following changes since commit 12ade69c1eb9958b13374edf5ef742ea20ccffde:

  KVM: PPC: Book3S HV: XIVE: Ensure VP isn't already in use (2019-10-15 16:09:11 +1100)

are available in the git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/paulus/powerpc tags/kvm-ppc-next-5.5-1

for you to fetch changes up to 55d7004299eb917767761f01a208d50afad4f535:

  KVM: PPC: Book3S HV: Reject mflags=2 (LPCR[AIL]=2) ADDR_TRANS_MODE mode (2019-10-22 16:29:02 +1100)

----------------------------------------------------------------
KVM PPC update for 5.5

* Add capability to tell userspace whether we can single-step the guest.

* Improve the allocation of XIVE virtual processor IDs, to reduce the
  risk of running out of IDs when running many VMs on POWER9.

* Rewrite interrupt synthesis code to deliver interrupts in virtual
  mode when appropriate.

* Minor cleanups and improvements.

----------------------------------------------------------------
Fabiano Rosas (1):
      KVM: PPC: Report single stepping capability

Greg Kurz (5):
      KVM: PPC: Book3S HV: XIVE: Set kvm->arch.xive when VPs are allocated
      KVM: PPC: Book3S HV: XIVE: Show VP id in debugfs
      KVM: PPC: Book3S HV: XIVE: Compute the VP id in a common helper
      KVM: PPC: Book3S HV: XIVE: Make VP block size configurable
      KVM: PPC: Book3S HV: XIVE: Allow userspace to set the # of VPs

Leonardo Bras (2):
      KVM: PPC: Reduce calls to get current->mm by storing the value locally
      KVM: PPC: E500: Replace current->mm by kvm->mm

Nicholas Piggin (5):
      KVM: PPC: Book3S: Define and use SRR1_MSR_BITS
      KVM: PPC: Book3S: Replace reset_msr mmu op with inject_interrupt arch op
      KVM: PPC: Book3S HV: Reuse kvmppc_inject_interrupt for async guest delivery
      KVM: PPC: Book3S HV: Implement LPCR[AIL]=3 mode for injected interrupts
      KVM: PPC: Book3S HV: Reject mflags=2 (LPCR[AIL]=2) ADDR_TRANS_MODE mode

 Documentation/virt/kvm/api.txt          |   3 +
 Documentation/virt/kvm/devices/xics.txt |  14 +++-
 Documentation/virt/kvm/devices/xive.txt |   8 ++
 arch/powerpc/include/asm/kvm_host.h     |   1 -
 arch/powerpc/include/asm/kvm_ppc.h      |   1 +
 arch/powerpc/include/asm/reg.h          |  12 +++
 arch/powerpc/include/uapi/asm/kvm.h     |   3 +
 arch/powerpc/kvm/book3s.c               |  27 +------
 arch/powerpc/kvm/book3s.h               |   3 +
 arch/powerpc/kvm/book3s_32_mmu.c        |   6 --
 arch/powerpc/kvm/book3s_64_mmu.c        |  15 ----
 arch/powerpc/kvm/book3s_64_mmu_hv.c     |  24 ++----
 arch/powerpc/kvm/book3s_hv.c            |  28 ++-----
 arch/powerpc/kvm/book3s_hv_builtin.c    |  82 ++++++++++++++++----
 arch/powerpc/kvm/book3s_hv_nested.c     |   2 +-
 arch/powerpc/kvm/book3s_pr.c            |  40 +++++++++-
 arch/powerpc/kvm/book3s_xive.c          | 128 +++++++++++++++++++++++++-------
 arch/powerpc/kvm/book3s_xive.h          |   5 ++
 arch/powerpc/kvm/book3s_xive_native.c   |  38 ++++------
 arch/powerpc/kvm/e500_mmu_host.c        |   6 +-
 arch/powerpc/kvm/powerpc.c              |   2 +
 include/uapi/linux/kvm.h                |   1 +
 22 files changed, 288 insertions(+), 161 deletions(-)
```
#### [PATCH 1/1] KVM: s390:  Add memcg accounting to KVM allocations
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11221463
Return-Path: <SRS0=FBlN=YY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B9C691668
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 31 Oct 2019 15:19:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 96F1A208C0
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 31 Oct 2019 15:19:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728311AbfJaPTa (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 31 Oct 2019 11:19:30 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:50460 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726642AbfJaPTa (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 31 Oct 2019 11:19:30 -0400
Received: from pps.filterd (m0098413.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x9VFGVYO134757
        for <kvm@vger.kernel.org>; Thu, 31 Oct 2019 11:19:28 -0400
Received: from e06smtp05.uk.ibm.com (e06smtp05.uk.ibm.com [195.75.94.101])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2w01ph1ak8-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 31 Oct 2019 11:19:28 -0400
Received: from localhost
        by e06smtp05.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <borntraeger@de.ibm.com>;
        Thu, 31 Oct 2019 15:19:26 -0000
Received: from b06cxnps3074.portsmouth.uk.ibm.com (9.149.109.194)
        by e06smtp05.uk.ibm.com (192.168.101.135) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Thu, 31 Oct 2019 15:19:23 -0000
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x9VFJM8R32571626
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 31 Oct 2019 15:19:22 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 585A752052;
        Thu, 31 Oct 2019 15:19:22 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTPS id 3F07B5204E;
        Thu, 31 Oct 2019 15:19:22 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 25651)
        id 0186EE0264; Thu, 31 Oct 2019 16:19:21 +0100 (CET)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Janosch Frank <frankja@linux.vnet.ibm.com>
Cc: KVM <kvm@vger.kernel.org>, Cornelia Huck <cohuck@redhat.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        linux-s390 <linux-s390@vger.kernel.org>,
        Thomas Huth <thuth@redhat.com>
Subject: [PATCH 1/1] KVM: s390:  Add memcg accounting to KVM allocations
Date: Thu, 31 Oct 2019 16:19:21 +0100
X-Mailer: git-send-email 2.21.0
In-Reply-To: <20191031151921.31871-1-borntraeger@de.ibm.com>
References: <20191031151921.31871-1-borntraeger@de.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 19103115-0020-0000-0000-000003815CBC
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19103115-0021-0000-0000-000021D773CC
Message-Id: <20191031151921.31871-2-borntraeger@de.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-10-31_06:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=2 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=902 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1908290000 definitions=main-1910310155
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

While I propared my KVM Forum talk about whats new in KVM including
memcg, I realized that the s390 code does not take care of memcg.

As far as I can tell, almost all kvm allocations in the s390x KVM code
can be attributed to process that triggers the allocation (in other
words, no global allocation for other guests). This will help the memcg
controller to do the right decisions.

Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 arch/s390/kvm/guestdbg.c  |  8 ++++----
 arch/s390/kvm/intercept.c |  2 +-
 arch/s390/kvm/interrupt.c | 12 ++++++------
 arch/s390/kvm/kvm-s390.c  | 22 +++++++++++-----------
 arch/s390/kvm/priv.c      |  4 ++--
 arch/s390/kvm/vsie.c      |  4 ++--
 6 files changed, 26 insertions(+), 26 deletions(-)

```
#### [tip: core/rcu] x86/kvm/pmu: Replace rcu_swap_protected() with rcu_replace_pointer()
##### From: "tip-bot2 for Paul E. McKenney" <tip-bot2@linutronix.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: "tip-bot2 for Paul E. McKenney"
 <tip-bot2@linutronix.de>
X-Patchwork-Id: 11221087
Return-Path: <SRS0=FBlN=YY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0DD2C112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 31 Oct 2019 11:58:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E95A52173E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 31 Oct 2019 11:58:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727995AbfJaL6X convert rfc822-to-8bit (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 31 Oct 2019 07:58:23 -0400
Received: from Galois.linutronix.de ([193.142.43.55]:55244 "EHLO
        Galois.linutronix.de" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726878AbfJaLzE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 31 Oct 2019 07:55:04 -0400
Received: from [5.158.153.53] (helo=tip-bot2.lab.linutronix.de)
        by Galois.linutronix.de with esmtpsa
 (TLS1.2:DHE_RSA_AES_256_CBC_SHA256:256)
        (Exim 4.80)
        (envelope-from <tip-bot2@linutronix.de>)
        id 1iQ92Z-0002rW-H8; Thu, 31 Oct 2019 12:54:59 +0100
Received: from [127.0.1.1] (localhost [IPv6:::1])
        by tip-bot2.lab.linutronix.de (Postfix) with ESMTP id 1654C1C0070;
        Thu, 31 Oct 2019 12:54:56 +0100 (CET)
Date: Thu, 31 Oct 2019 11:54:55 -0000
From: "tip-bot2 for Paul E. McKenney" <tip-bot2@linutronix.de>
Reply-to: linux-kernel@vger.kernel.org
To: linux-tip-commits@vger.kernel.org
Subject: [tip: core/rcu] x86/kvm/pmu: Replace rcu_swap_protected() with
 rcu_replace_pointer()
Cc: Linus Torvalds <torvalds@linux-foundation.org>,
 "Paul E. McKenney" <paulmck@kernel.org>, Paolo Bonzini <pbonzini@redhat.com>,
 Radim =?utf-8?b?S3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Thomas Gleixner <tglx@linutronix.de>, Ingo Molnar <mingo@redhat.com>,
 Borislav Petkov <bp@alien8.de>, "H. Peter Anvin" <hpa@zytor.com>,
 <x86@kernel.org>, <kvm@vger.kernel.org>, Ingo Molnar <mingo@kernel.org>,
 linux-kernel@vger.kernel.org
MIME-Version: 1.0
Message-ID: <157252289579.29376.8178836820582764127.tip-bot2@tip-bot2>
X-Mailer: tip-git-log-daemon
Robot-ID: <tip-bot2.linutronix.de>
Robot-Unsubscribe: Contact <mailto:tglx@linutronix.de> to get blacklisted from
 these emails
X-Linutronix-Spam-Score: -1.0
X-Linutronix-Spam-Level: -
X-Linutronix-Spam-Status: No , -1.0 points, 5.0 required,
  ALL_TRUSTED=-1,SHORTCIRCUIT=-0.0001
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The following commit has been merged into the core/rcu branch of tip:

Commit-ID:     12e78e6902134c9e49b2481c2515555e6f7b12dc
Gitweb:        https://git.kernel.org/tip/12e78e6902134c9e49b2481c2515555e6f7b12dc
Author:        Paul E. McKenney <paulmck@kernel.org>
AuthorDate:    Mon, 23 Sep 2019 15:15:35 -07:00
Committer:     Paul E. McKenney <paulmck@kernel.org>
CommitterDate: Wed, 30 Oct 2019 08:43:51 -07:00

x86/kvm/pmu: Replace rcu_swap_protected() with rcu_replace_pointer()

This commit replaces the use of rcu_swap_protected() with the more
intuitively appealing rcu_replace_pointer() as a step towards removing
rcu_swap_protected().

Link: https://lore.kernel.org/lkml/CAHk-=wiAsJLw1egFEE=Z7-GGtM6wcvtyytXZA1+BHqta4gg6Hw@mail.gmail.com/
Reported-by: Linus Torvalds <torvalds@linux-foundation.org>
[ paulmck: From rcu_replace() to rcu_replace_pointer() per Ingo Molnar. ]
Signed-off-by: Paul E. McKenney <paulmck@kernel.org>
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
Cc: "Radim Krčmář" <rkrcmar@redhat.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Borislav Petkov <bp@alien8.de>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: <x86@kernel.org>
Cc: <kvm@vger.kernel.org>
---
 arch/x86/kvm/pmu.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH v4] vhost: introduce mdev based hardware backend
##### From: Tiwei Bie <tiwei.bie@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tiwei Bie <tiwei.bie@intel.com>
X-Patchwork-Id: 11221281
Return-Path: <SRS0=FBlN=YY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B87191515
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 31 Oct 2019 14:00:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8D03121734
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 31 Oct 2019 14:00:38 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728020AbfJaOAd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 31 Oct 2019 10:00:33 -0400
Received: from mga01.intel.com ([192.55.52.88]:4165 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727647AbfJaOAc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 31 Oct 2019 10:00:32 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga003.jf.intel.com ([10.7.209.27])
  by fmsmga101.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 31 Oct 2019 07:00:32 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.68,250,1569308400";
   d="scan'208";a="203540220"
Received: from dpdk-virtio-tbie-2.sh.intel.com ([10.67.104.74])
  by orsmga003.jf.intel.com with ESMTP; 31 Oct 2019 07:00:28 -0700
From: Tiwei Bie <tiwei.bie@intel.com>
To: mst@redhat.com, jasowang@redhat.com, alex.williamson@redhat.com,
        maxime.coquelin@redhat.com
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        dan.daly@intel.com, cunming.liang@intel.com,
        zhihong.wang@intel.com, lingshan.zhu@intel.com, tiwei.bie@intel.com
Subject: [PATCH v4] vhost: introduce mdev based hardware backend
Date: Thu, 31 Oct 2019 22:01:14 +0800
Message-Id: <20191031140114.25615-1-tiwei.bie@intel.com>
X-Mailer: git-send-email 2.23.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch introduces a mdev based hardware vhost backend.
This backend is built on top of the same abstraction used
in virtio-mdev and provides a generic vhost interface for
userspace to accelerate the virtio devices in guest.

This backend is implemented as a mdev device driver on top
of the same mdev device ops used in virtio-mdev but using
a different mdev class id, and it will register the device
as a VFIO device for userspace to use. Userspace can setup
the IOMMU with the existing VFIO container/group APIs and
then get the device fd with the device name. After getting
the device fd of this device, userspace can use vhost ioctls
to setup the backend.

Signed-off-by: Tiwei Bie <tiwei.bie@intel.com>
---
This patch depends on below series:
https://lkml.org/lkml/2019/10/30/62

v3 -> v4:
- Rebase on top of virtio-mdev series v6;
- Some minor tweaks and improvements;

v2 -> v3:
- Fix the return value (Jason);
- Don't cache unnecessary information in vhost-mdev (Jason);
- Get rid of the memset in open (Jason);
- Add comments for VHOST_SET_MEM_TABLE, ... (Jason);
- Filter out unsupported features in vhost-mdev (Jason);
- Add _GET_DEVICE_ID ioctl (Jason);
- Add _GET_CONFIG/_SET_CONFIG ioctls (Jason);
- Drop _GET_QUEUE_NUM ioctl (Jason);
- Fix the copy-paste errors in _IOW/_IOR usage;
- Some minor fixes and improvements;

v1 -> v2:
- Replace _SET_STATE with _SET_STATUS (MST);
- Check status bits at each step (MST);
- Report the max ring size and max number of queues (MST);
- Add missing MODULE_DEVICE_TABLE (Jason);
- Only support the network backend w/o multiqueue for now;
- Some minor fixes and improvements;
- Rebase on top of virtio-mdev series v4;

RFC v4 -> v1:
- Implement vhost-mdev as a mdev device driver directly and
  connect it to VFIO container/group. (Jason);
- Pass ring addresses as GPAs/IOVAs in vhost-mdev to avoid
  meaningless HVA->GPA translations (Jason);

RFC v3 -> RFC v4:
- Build vhost-mdev on top of the same abstraction used by
  virtio-mdev (Jason);
- Introduce vhost fd and pass VFIO fd via SET_BACKEND ioctl (MST);

RFC v2 -> RFC v3:
- Reuse vhost's ioctls instead of inventing a VFIO regions/irqs
  based vhost protocol on top of vfio-mdev (Jason);

RFC v1 -> RFC v2:
- Introduce a new VFIO device type to build a vhost protocol
  on top of vfio-mdev;

 drivers/vfio/mdev/mdev_core.c    |  20 ++
 drivers/vfio/mdev/mdev_private.h |   1 +
 drivers/vhost/Kconfig            |  12 +
 drivers/vhost/Makefile           |   3 +
 drivers/vhost/mdev.c             | 556 +++++++++++++++++++++++++++++++
 include/linux/mdev.h             |   5 +
 include/uapi/linux/vhost.h       |  18 +
 include/uapi/linux/vhost_types.h |   8 +
 8 files changed, 623 insertions(+)
 create mode 100644 drivers/vhost/mdev.c

```
