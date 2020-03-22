#### [PATCH v3 1/9] KVM: Pass kvm_init()'s opaque param to additional arch funcs
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11451379
Return-Path: <SRS0=9K6R=5G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 147FC13B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 21 Mar 2020 20:27:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E7F962076E
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 21 Mar 2020 20:26:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727799AbgCUU0H (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 21 Mar 2020 16:26:07 -0400
Received: from mga03.intel.com ([134.134.136.65]:8930 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726146AbgCUU0H (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 21 Mar 2020 16:26:07 -0400
IronPort-SDR: 
 qPmlwfU02OC9s0qWuZ6ZLrUzl9dVV5mxnmgzJXlsduHVXGhQLg+gUJF4klSOC5cnuS5YIpmAwr
 BwSLp7ZIXlBw==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 21 Mar 2020 13:26:05 -0700
IronPort-SDR: 
 scn7pZUQDpTF3SQ9rG37pbebi3mtbty3HtYRPENAnoNHIWqdnH+Q8Df4p/ny8v2N2HzwcoFbwe
 7DKC+AlU6sCw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,289,1580803200";
   d="scan'208";a="280773535"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga002.fm.intel.com with ESMTP; 21 Mar 2020 13:26:04 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Paul Mackerras <paulus@ozlabs.org>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, Marc Zyngier <maz@kernel.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        linux-mips@vger.kernel.org, kvm@vger.kernel.org,
        kvm-ppc@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, linux-kernel@vger.kernel.org
Subject: [PATCH v3 1/9] KVM: Pass kvm_init()'s opaque param to additional arch
 funcs
Date: Sat, 21 Mar 2020 13:25:55 -0700
Message-Id: <20200321202603.19355-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200321202603.19355-1-sean.j.christopherson@intel.com>
References: <20200321202603.19355-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Pass @opaque to kvm_arch_hardware_setup() and
kvm_arch_check_processor_compat() to allow architecture specific code to
reference @opaque without having to stash it away in a temporary global
variable.  This will enable x86 to separate its vendor specific callback
ops, which are passed via @opaque, into "init" and "runtime" ops without
having to stash away the "init" ops.

No functional change intended.

Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Tested-by: Cornelia Huck <cohuck@redhat.com> #s390
Acked-by: Marc Zyngier <maz@kernel.org>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/mips/kvm/mips.c       |  4 ++--
 arch/powerpc/kvm/powerpc.c |  4 ++--
 arch/s390/kvm/kvm-s390.c   |  4 ++--
 arch/x86/kvm/x86.c         |  4 ++--
 include/linux/kvm_host.h   |  4 ++--
 virt/kvm/arm/arm.c         |  4 ++--
 virt/kvm/kvm_main.c        | 18 ++++++++++++++----
 7 files changed, 26 insertions(+), 16 deletions(-)

```
#### [PATCH v2 1/3] KVM: VMX: Always VMCLEAR in-use VMCSes during crash with kexec support
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11451327
Return-Path: <SRS0=9K6R=5G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 69D2D13B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 21 Mar 2020 19:38:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 48AD220777
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 21 Mar 2020 19:38:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727932AbgCUThy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 21 Mar 2020 15:37:54 -0400
Received: from mga11.intel.com ([192.55.52.93]:55983 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727028AbgCUThy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 21 Mar 2020 15:37:54 -0400
IronPort-SDR: 
 Gwu08gbtiuFj/OhEBY9nrkPQ+oBnhAh4D1tzSHd/ozgmF7LNavET69wkRpGsXD3PWEnFSuLQLe
 pl0RV5BYHEmA==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by fmsmga102.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 21 Mar 2020 12:37:53 -0700
IronPort-SDR: 
 efQx6clHZAyfj791VdGLAKKVJr/L0nd1o6q2vwvK/bk2MMYKNy1k0tTcaOuvtZATFdNToDKrsg
 +w4SkRO08jUA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,289,1580803200";
   d="scan'208";a="445353678"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga005.fm.intel.com with ESMTP; 21 Mar 2020 12:37:52 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2 1/3] KVM: VMX: Always VMCLEAR in-use VMCSes during crash
 with kexec support
Date: Sat, 21 Mar 2020 12:37:49 -0700
Message-Id: <20200321193751.24985-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200321193751.24985-1-sean.j.christopherson@intel.com>
References: <20200321193751.24985-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

VMCLEAR all in-use VMCSes during a crash, even if kdump's NMI shootdown
interrupted a KVM update of the percpu in-use VMCS list.

Because NMIs are not blocked by disabling IRQs, it's possible that
crash_vmclear_local_loaded_vmcss() could be called while the percpu list
of VMCSes is being modified, e.g. in the middle of list_add() in
vmx_vcpu_load_vmcs().  This potential corner case was called out in the
original commit[*], but the analysis of its impact was wrong.

Skipping the VMCLEARs is wrong because it all but guarantees that a
loaded, and therefore cached, VMCS will live across kexec and corrupt
memory in the new kernel.  Corruption will occur because the CPU's VMCS
cache is non-coherent, i.e. not snooped, and so the writeback of VMCS
memory on its eviction will overwrite random memory in the new kernel.
The VMCS will live because the NMI shootdown also disables VMX, i.e. the
in-progress VMCLEAR will #UD, and existing Intel CPUs do not flush the
VMCS cache on VMXOFF.

Furthermore, interrupting list_add() and list_del() is safe due to
crash_vmclear_local_loaded_vmcss() using forward iteration.  list_add()
ensures the new entry is not visible to forward iteration unless the
entire add completes, via WRITE_ONCE(prev->next, new).  A bad "prev"
pointer could be observed if the NMI shootdown interrupted list_del() or
list_add(), but list_for_each_entry() does not consume ->prev.

In addition to removing the temporary disabling of VMCLEAR, open code
loaded_vmcs_init() in __loaded_vmcs_clear() and reorder VMCLEAR so that
the VMCS is deleted from the list only after it's been VMCLEAR'd.
Deleting the VMCS before VMCLEAR would allow a race where the NMI
shootdown could arrive between list_del() and vmcs_clear() and thus
neither flow would execute a successful VMCLEAR.  Alternatively, more
code could be moved into loaded_vmcs_init(), but that gets rather silly
as the only other user, alloc_loaded_vmcs(), doesn't need the smp_wmb()
and would need to work around the list_del().

Update the smp_*() comments related to the list manipulation, and
opportunistically reword them to improve clarity.

[*] https://patchwork.kernel.org/patch/1675731/#3720461

Fixes: 8f536b7697a0 ("KVM: VMX: provide the vmclear function and a bitmap to support VMCLEAR in kdump")
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/vmx.c | 67 ++++++++++--------------------------------
 1 file changed, 16 insertions(+), 51 deletions(-)

```
#### [PATCH] x86: vmx: Fix "EPT violation - paging structure" test
##### From: Nadav Amit <namit@vmware.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nadav Amit <namit@vmware.com>
X-Patchwork-Id: 11450707
Return-Path: <SRS0=9K6R=5G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1A8C9139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 21 Mar 2020 05:07:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id EF5D320753
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 21 Mar 2020 05:07:50 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727882AbgCUFHu (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 21 Mar 2020 01:07:50 -0400
Received: from mail-pf1-f193.google.com ([209.85.210.193]:33947 "EHLO
        mail-pf1-f193.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725440AbgCUFHu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 21 Mar 2020 01:07:50 -0400
Received: by mail-pf1-f193.google.com with SMTP id 23so4417919pfj.1
        for <kvm@vger.kernel.org>; Fri, 20 Mar 2020 22:07:49 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=49BuhoPB/LV65DGt5z0/eg7O0OzojYhf2QWVo/kHTnA=;
        b=dlQ0FbvDSrgCI0wUxafmy5v/Kc8YogcDi05k6GIU7914IandyOgaBIou0Mg0eIl2aZ
         2CWfSSSPzSrCG/CR/o/rOLaUlWyBmDbZDHaaxwWXfotRwTBURVAQsEZy17FvoDPmjA5o
         LZTe7FCmt8coKM/LooAlE+PlmmrF3uek5zegWlkvJ3tBqkYY+p2jhSNySfo6M2TcvXfu
         bJU5AS2fYgm8yRadIwAcip4+Kpu1/Uk/IUzwj1lFiiNOnNGju7W0PDunItUw02Uz313W
         pbR+yaLFEPjbCqJ8+c8JI6gbjTN6ejWC4RKe5sqMza+JhG3ZVVqyHA4DOIVFIk92N9NP
         HUdw==
X-Gm-Message-State: ANhLgQ1apckc7jhYAqkoFzfvAzTXObhGqIiP3dXDu9MSnpONM/qaWQYH
        mRJ/sOsfNDEMoQ0GtlokORvw0BpYNJA=
X-Google-Smtp-Source: 
 ADFU+vtcFs9SIAbeve8621dMFSO4oz9Sa937sKD5p1tsYNgB7EMgNFJ7j12QgwE/c64Omfw907l76g==
X-Received: by 2002:aa7:9888:: with SMTP id r8mr13526553pfl.293.1584767268664;
        Fri, 20 Mar 2020 22:07:48 -0700 (PDT)
Received: from sc2-haas01-esx0118.eng.vmware.com ([66.170.99.1])
        by smtp.gmail.com with ESMTPSA id
 b9sm6391524pgi.75.2020.03.20.22.07.47
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 20 Mar 2020 22:07:47 -0700 (PDT)
From: Nadav Amit <namit@vmware.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org, Nadav Amit <namit@vmware.com>
Subject: [PATCH] x86: vmx: Fix "EPT violation - paging structure" test
Date: Fri, 20 Mar 2020 22:05:55 -0700
Message-Id: <20200321050555.4212-1-namit@vmware.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Running the tests with more than 4GB of memory results in the following
failure:

  FAIL: EPT violation - paging structure

It appears that the test mistakenly used get_ept_pte() to retrieve the
guest PTE, but this function is intended for accessing EPT and not the
guest page tables. Use get_pte_level() instead of get_ept_pte().

Tested on bare-metal only.

Signed-off-by: Nadav Amit <namit@vmware.com>
---
 x86/vmx_tests.c | 17 +++++++++--------
 1 file changed, 9 insertions(+), 8 deletions(-)

```
#### [PATCH] x86: vmx: skip atomic_switch_overflow_msrs_test on bare metal
##### From: Nadav Amit <namit@vmware.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nadav Amit <namit@vmware.com>
X-Patchwork-Id: 11450709
Return-Path: <SRS0=9K6R=5G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A2EA7139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 21 Mar 2020 05:08:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7EDD020757
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 21 Mar 2020 05:08:08 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727920AbgCUFIH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 21 Mar 2020 01:08:07 -0400
Received: from mail-pj1-f66.google.com ([209.85.216.66]:50180 "EHLO
        mail-pj1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725763AbgCUFIH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 21 Mar 2020 01:08:07 -0400
Received: by mail-pj1-f66.google.com with SMTP id v13so3432359pjb.0
        for <kvm@vger.kernel.org>; Fri, 20 Mar 2020 22:08:07 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=8T9VA2UuKy0j0X4+DGwUzC/m9/KOGf3YA0PhfRdA/9s=;
        b=acNtUwjDAwimQVHMks/LR4xNke99CYUdsjIo7dXW5893xfL/voNh9DTCuBb9S3RlNA
         Rp/8nVGng0aDVCNAT1UH6t+b2pxPXSMTjPIYB3BeD706F15z/4esucRccFw7Zr6bPGBt
         s8e8IwAiKqohUHPgYzmRw2GgKhneLQKoR1qPV7wKYm/TKf8pelFWOa4TgOgaINa0IoU3
         T9gylz7r+LGcusAL7+Zhp+3axfbTz403qpRkA2xG4+tZKCeV1eJuhV7/bpV6ZJedyEe8
         hdpqBKvcaMVHxVONBkvoL/Mjl8DL47D15C0u+OZe/Nnz1Y04Dj3STNk45oDB1umFRBQ6
         UPKQ==
X-Gm-Message-State: ANhLgQ2ZbOjYqcGmD9i3ceqe277Ie+3THhwPEXgCD7Cg+Rdyk9QKxp/S
        9azUFparMu8bHH3xXIVFdzo=
X-Google-Smtp-Source: 
 ADFU+vt6bJv1ff3Wn9YyPuBApQUkLsg+akjcds7MRl+dN8mVXEco1G/4AzVZ65dTZJfReIvM7CUc9A==
X-Received: by 2002:a17:90a:dd42:: with SMTP id
 u2mr13247435pjv.10.1584767286510;
        Fri, 20 Mar 2020 22:08:06 -0700 (PDT)
Received: from sc2-haas01-esx0118.eng.vmware.com ([66.170.99.1])
        by smtp.gmail.com with ESMTPSA id
 h132sm7148179pfe.118.2020.03.20.22.08.05
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 20 Mar 2020 22:08:05 -0700 (PDT)
From: Nadav Amit <namit@vmware.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org, Nadav Amit <namit@vmware.com>,
        Marc Orr <marcorr@google.com>
Subject: [PATCH] x86: vmx: skip atomic_switch_overflow_msrs_test on bare metal
Date: Fri, 20 Mar 2020 22:06:16 -0700
Message-Id: <20200321050616.4272-1-namit@vmware.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The test atomic_switch_overflow_msrs_test is only expected to pass on
KVM. Skip the test when the debug device is not supported to avoid
failures on bare-metal.

Cc: Marc Orr <marcorr@google.com>
Signed-off-by: Nadav Amit <namit@vmware.com>
---
 x86/vmx_tests.c | 5 ++++-
 1 file changed, 4 insertions(+), 1 deletion(-)

```
