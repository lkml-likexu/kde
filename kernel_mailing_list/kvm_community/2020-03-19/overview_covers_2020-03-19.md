

#### [PATCH v7 0/5] x86/kvm/hyper-v: add support for synthetic debugger
##### From: Jon Doron <arilou@gmail.com>

```c
From patchwork Thu Mar 19 05:58:37 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jon Doron <arilou@gmail.com>
X-Patchwork-Id: 11446517
Return-Path: <SRS0=MMtT=5E=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 021F31392
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Mar 2020 05:59:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D591220757
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Mar 2020 05:58:59 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="UDJ7/1W6"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727011AbgCSF67 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 19 Mar 2020 01:58:59 -0400
Received: from mail-wm1-f66.google.com ([209.85.128.66]:56127 "EHLO
        mail-wm1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725747AbgCSF67 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 19 Mar 2020 01:58:59 -0400
Received: by mail-wm1-f66.google.com with SMTP id 6so627300wmi.5;
        Wed, 18 Mar 2020 22:58:57 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=OWn1mIT2Bjb41CmPi8mP+JBp2pXqXnT3uc7wL4wPFfk=;
        b=UDJ7/1W6rCWk3HuWUqETnkxwC2HVaH4COHKvtN5D0wJr+RPVcshC0zyA+Hg+g+/Iys
         nhzda9O2UzEPjjOvsmq/C5Y4G5tynGheLnYUN+RU8Gm9AtRS/2sWuKhgv1Ma6flC2mnK
         E8JZIP9RIP9n4R56Zqfwultve5jX7tR5Q2g8pJpP+zEo3ZKr/dfkG2lSbFJJOPeGkFo9
         UivJxEQh4S8tIcii1CsDVHCdUVMBxtIxzEcNnGbbuuqts8vYlA4Ipk3xl4ZcIdkvfl5i
         phVleJs627vb3qb+TWsUAhBPW7kGlqTZWyP+/bVc6mzCAFSft+dApGfs1evi1/FTw9tH
         qXAQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=OWn1mIT2Bjb41CmPi8mP+JBp2pXqXnT3uc7wL4wPFfk=;
        b=bOQS8xDYkRMQKVjRTfJnV8j358Elom0Gvj8b+2tD21n9WqujlSS9/EDC3nPjdap/kY
         2Ir2CVbAcNh1yTyO8j5CqQOkRuX7VE0SVUL1mmqPg86QCyx+twW7MpFVT0goaO8UZPr2
         7H2Pj50+Rl8CALQ38O2XdCW1HseURQQFYKYRu11igZ4dfXAmcw2SUuwTwnYSLgc6YsQF
         9i83b4I1CzZRPAYRasdgwzD2+gjf1lY+iXlvLhfnZ6vCM2aZGgZdNadooOFwK2yId4/J
         HQTUC00xXiEYm/YIUsDwoCGr4exEoh4V4BmZMmxN+R5q6ATtzwr1gJ/JfI/ciK0XduMy
         4xtg==
X-Gm-Message-State: ANhLgQ28E4lAk9gaJMO5FXVgrJWhXabsNT2oZTu7t8Uu3pCWRtbhWvZW
        Wc7N6OzANQOevZNiN9iH1O1HSyYu3OY=
X-Google-Smtp-Source: 
 ADFU+vvn7IqrHJg02ILGeDBVCEexjz30hIOviyWE6cPLKQGeaYpJkS4liq3odMuLq/9DVdPuY+rQ6g==
X-Received: by 2002:a7b:c414:: with SMTP id k20mr1557534wmi.119.1584597536758;
        Wed, 18 Mar 2020 22:58:56 -0700 (PDT)
Received: from jondnuc.lan (IGLD-84-229-155-229.inter.net.il.
 [84.229.155.229])
        by smtp.gmail.com with ESMTPSA id
 n2sm1884174wro.25.2020.03.18.22.58.54
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 18 Mar 2020 22:58:56 -0700 (PDT)
From: Jon Doron <arilou@gmail.com>
To: kvm@vger.kernel.org, linux-hyperv@vger.kernel.org
Cc: vkuznets@redhat.com, Jon Doron <arilou@gmail.com>
Subject: [PATCH v7 0/5] x86/kvm/hyper-v: add support for synthetic debugger
Date: Thu, 19 Mar 2020 07:58:37 +0200
Message-Id: <20200319055842.673513-1-arilou@gmail.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add support for the synthetic debugger interface of hyper-v, the
synthetic debugger has 2 modes.
1. Use a set of MSRs to send/recv information (undocumented so it's not
   going to the hyperv-tlfs.h)
2. Use hypercalls

The first mode is based the following MSRs:
1. Control/Status MSRs which either asks for a send/recv .
2. Send/Recv MSRs each holds GPA where the send/recv buffers are.
3. Pending MSR, holds a GPA to a PAGE that simply has a boolean that
   indicates if there is data pending to issue a recv VMEXIT.

The first mode implementation is to simply exit to user-space when
either the control MSR or the pending MSR are being set.
Then it's up-to userspace to implement the rest of the logic of sending/recving.

In the second mode instead of using MSRs KNet will simply issue
Hypercalls with the information to send/recv, in this mode the data
being transferred is UDP encapsulated, unlike in the previous mode in
which you get just the data to send.

The new hypercalls will exit to userspace which will be incharge of
re-encapsulating if needed the UDP packets to be sent.

There is an issue though in which KDNet does not respect the hypercall
page and simply issues vmcall/vmmcall instructions depending on the cpu
type expecting them to be handled as it a real hypercall was issued.

It's important to note that part of this feature has been subject to be
removed in future versions of Windows, which is why some of the
defintions will not be present the the TLFS but in the kvm hyperv header
instead.

Jon Doron (5):
  x86/kvm/hyper-v: Explicitly align hcall param for kvm_hyperv_exit
  x86/hyper-v: Add synthetic debugger definitions
  x86/kvm/hyper-v: Add support for synthetic debugger capability
  x86/kvm/hyper-v: enable hypercalls without hypercall page with syndbg
  x86/kvm/hyper-v: Add support for synthetic debugger via hypercalls

 Documentation/virt/kvm/api.rst     |  18 +++
 arch/x86/include/asm/hyperv-tlfs.h |   6 +
 arch/x86/include/asm/kvm_host.h    |  14 +++
 arch/x86/kvm/hyperv.c              | 177 ++++++++++++++++++++++++++++-
 arch/x86/kvm/hyperv.h              |  33 ++++++
 arch/x86/kvm/trace.h               |  51 +++++++++
 arch/x86/kvm/x86.c                 |  13 +++
 include/uapi/linux/kvm.h           |  13 +++
 8 files changed, 323 insertions(+), 2 deletions(-)
```
#### [PATCH v2 0/5] PEBS virtualization enabling via Intel PT
##### From: Luwei Kang <luwei.kang@intel.com>

```c
From patchwork Thu Mar 19 14:33:45 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Luwei Kang <luwei.kang@intel.com>
X-Patchwork-Id: 11446543
Return-Path: <SRS0=MMtT=5E=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E037413B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Mar 2020 06:35:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C931A20409
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Mar 2020 06:35:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727011AbgCSGfb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 19 Mar 2020 02:35:31 -0400
Received: from mga01.intel.com ([192.55.52.88]:51299 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725812AbgCSGfa (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 19 Mar 2020 02:35:30 -0400
IronPort-SDR: 
 jAqTvka35ViE+GAudoZ/cQaT25DXIoZPuRaNUSHWRYZTDSlA31jziqYiK0+UCW/ux9Vw/SzvCI
 P7O59klnAFsQ==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga006.jf.intel.com ([10.7.209.51])
  by fmsmga101.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 18 Mar 2020 23:35:30 -0700
IronPort-SDR: 
 JjJIFAbFGye2coKeGQkBdUKDRzZ8ruE0DyVb+H5EoqBg/iQ1rysMNE1vEQvWG+R1YVs0y+Ffo6
 MZGgRTdhYMnA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,570,1574150400";
   d="scan'208";a="248439070"
Received: from snr.bj.intel.com ([10.240.193.90])
  by orsmga006.jf.intel.com with ESMTP; 18 Mar 2020 23:35:24 -0700
From: Luwei Kang <luwei.kang@intel.com>
To: x86@kernel.org, linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: peterz@infradead.org, mingo@redhat.com, acme@kernel.org,
        mark.rutland@arm.com, alexander.shishkin@linux.intel.com,
        jolsa@redhat.com, namhyung@kernel.org, tglx@linutronix.de,
        bp@alien8.de, hpa@zytor.com, pbonzini@redhat.com,
        sean.j.christopherson@intel.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        pawan.kumar.gupta@linux.intel.com, ak@linux.intel.com,
        thomas.lendacky@amd.com, fenghua.yu@intel.com,
        kan.liang@linux.intel.com, Luwei Kang <luwei.kang@intel.com>
Subject: [PATCH v2 0/5] PEBS virtualization enabling via Intel PT
Date: Thu, 19 Mar 2020 22:33:45 +0800
Message-Id: <1584628430-23220-1-git-send-email-luwei.kang@intel.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Intel new hardware(Atom processors based on the Tremont
microarchitecture) introduces some Processor Event-Based Sampling(PEBS)
extensions that output the PEBS record to Intel PT stream instead of DS
area. The PEBS record will be packaged in a specific format when
outputting to Intel PT.

This patch set will enable PEBS functionality in KVM Guest by PEBS output
to Intel PT, base on PEBS virtualization enabling via DS patch set[1].

Compared to the v1, the common code of PEBS virtualization enabling(PEBS
via DS and PEBS via Intel PT) has been moved to PEBS via DS patch set.
This patch set only includes the PEBS via PT specific changes.

Patch 1 is an extension to get fixed function counter by reload MSRs;
Patch 2,3 implement the CPUID and MSRs emulation;
Patch 4 will add the counter reload MSRs to MSR list during VM-entry/exit;
Patch 5 will swith the PEBS records to Intel PT buffer if PEBS via PT is
        enabled in KVM guest.

[1]: https://lore.kernel.org/kvm/1583431025-19802-1-git-send-email-luwei.kang@intel.com/

Luwei Kang (5):
  KVM: x86/pmu: Add base address parameter for get_fixed_pmc function
  KVM: x86/pmu: Expose PDCM feature when PEBS output to PT
  KVM: x86/pmu: PEBS output Intel PT MSRs emulation
  KVM: x86/pmu: Add counter reload register to MSR list
  KVM: VMX: Switch PEBS records output to Intel PT buffer

 arch/x86/events/perf_event.h     |   5 --
 arch/x86/include/asm/kvm_host.h  |   2 +
 arch/x86/include/asm/msr-index.h |   6 +++
 arch/x86/kvm/pmu.h               |   6 +--
 arch/x86/kvm/vmx/capabilities.h  |   9 +++-
 arch/x86/kvm/vmx/pmu_intel.c     | 112 ++++++++++++++++++++++++++++++++++-----
 arch/x86/kvm/vmx/vmx.c           |   3 ++
 arch/x86/kvm/vmx/vmx.h           |   2 +-
 arch/x86/kvm/x86.c               |  32 +++++++++++
 9 files changed, 154 insertions(+), 23 deletions(-)
```
#### [PATCH v8 0/5] x86/kvm/hyper-v: add support for synthetic debugger
##### From: Jon Doron <arilou@gmail.com>

```c
From patchwork Thu Mar 19 06:38:31 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jon Doron <arilou@gmail.com>
X-Patchwork-Id: 11446557
Return-Path: <SRS0=MMtT=5E=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AAC881874
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Mar 2020 06:38:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 89A2320753
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Mar 2020 06:38:53 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="My9EpVpa"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727177AbgCSGiw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 19 Mar 2020 02:38:52 -0400
Received: from mail-wm1-f68.google.com ([209.85.128.68]:40550 "EHLO
        mail-wm1-f68.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727120AbgCSGiw (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 19 Mar 2020 02:38:52 -0400
Received: by mail-wm1-f68.google.com with SMTP id z12so700843wmf.5;
        Wed, 18 Mar 2020 23:38:49 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=gUcps1XM9Cn7Ral3obTmLHmlyiV6Ruxu367UiIJawY8=;
        b=My9EpVpa5DWwqQPRF2N8bCYCYC5/m49C3+ZuNWTRsSk8vPx9vBNRa/W+hnmcKq1kub
         uRXNkl01SJR33kVLqk3gyqBEsYww/ztTjq3fUzDLiphupb0D6ZkQ0LEqwtNSxwcnhg9D
         3pfC1m8cfDLN36utNyTiZnQZvZPkQDogwbbGsNCZKGO/2PCzp3WzEFO05KCAAnWp6Mh3
         wlU6i2LmWw6mSiKde3eloOf95h4hVm4pIl33tht86zx0mPC0+bJ/td8xpHplAzZA3OcG
         ACLQXgkCWb1uK5l+JOXpc8YlbzGQRwFT4z3dPxA9sUL4kPOPSNyvX2WACAAr6ViVCX6S
         o8sA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=gUcps1XM9Cn7Ral3obTmLHmlyiV6Ruxu367UiIJawY8=;
        b=oai7kGMa9VkXcTOChgnbexiQgJ0LKN4jZVlaGQgDmRfHb65kVjtTS/VBb/nmLsaX6x
         OENtFAEy16ye0Lf2Hej46SS5ZlFSj37WFrDQ0p/11Ywg1Kn1vkiAnrXFBAvohreSIyPB
         12vakT5/086UeWq8xvKrePRbII6oi92KPFk0jUadYQEYEL09wLZK5EhljT5k+yCb7rGG
         0RU2Mx4m1T/gSD2uPdnhxHj8BnuUcT/dlg85hhG72aS/9SpdYPJLTEMpIX9PojL9UBNG
         1HOxLNvbED66bhF+Pt3YNieEw+3MhopHQ4S9CIRAvIrOtNfqkrwV3muldAQ+c2YJ12V9
         FmCw==
X-Gm-Message-State: ANhLgQ214Qt3Iij0B2S3T09LC8JjGUonKRWSbrWQ24rGKrMP/mFV5APZ
        p+8I34Gmxn2MtcAjjCSTWyrgWLzrwQo=
X-Google-Smtp-Source: 
 ADFU+vtwpaGid4XmsOar+JdBuJb6aiDNGDn48cGf7cu+d0Kw8mwCD6O4raWD9X1iFlr1TUbfMe7/bA==
X-Received: by 2002:a7b:cd97:: with SMTP id y23mr1731000wmj.161.1584599928867;
        Wed, 18 Mar 2020 23:38:48 -0700 (PDT)
Received: from jondnuc.lan (IGLD-84-229-155-229.inter.net.il.
 [84.229.155.229])
        by smtp.gmail.com with ESMTPSA id
 l13sm1945665wrm.57.2020.03.18.23.38.47
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 18 Mar 2020 23:38:48 -0700 (PDT)
From: Jon Doron <arilou@gmail.com>
To: kvm@vger.kernel.org, linux-hyperv@vger.kernel.org
Cc: vkuznets@redhat.com, Jon Doron <arilou@gmail.com>
Subject: [PATCH v8 0/5] x86/kvm/hyper-v: add support for synthetic debugger
Date: Thu, 19 Mar 2020 08:38:31 +0200
Message-Id: <20200319063836.678562-1-arilou@gmail.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add support for the synthetic debugger interface of hyper-v, the
synthetic debugger has 2 modes.
1. Use a set of MSRs to send/recv information (undocumented so it's not
   going to the hyperv-tlfs.h)
2. Use hypercalls

The first mode is based the following MSRs:
1. Control/Status MSRs which either asks for a send/recv .
2. Send/Recv MSRs each holds GPA where the send/recv buffers are.
3. Pending MSR, holds a GPA to a PAGE that simply has a boolean that
   indicates if there is data pending to issue a recv VMEXIT.

The first mode implementation is to simply exit to user-space when
either the control MSR or the pending MSR are being set.
Then it's up-to userspace to implement the rest of the logic of sending/recving.

In the second mode instead of using MSRs KNet will simply issue
Hypercalls with the information to send/recv, in this mode the data
being transferred is UDP encapsulated, unlike in the previous mode in
which you get just the data to send.

The new hypercalls will exit to userspace which will be incharge of
re-encapsulating if needed the UDP packets to be sent.

There is an issue though in which KDNet does not respect the hypercall
page and simply issues vmcall/vmmcall instructions depending on the cpu
type expecting them to be handled as it a real hypercall was issued.

It's important to note that part of this feature has been subject to be
removed in future versions of Windows, which is why some of the
defintions will not be present the the TLFS but in the kvm hyperv header
instead.

Jon Doron (5):
  x86/kvm/hyper-v: Explicitly align hcall param for kvm_hyperv_exit
  x86/hyper-v: Add synthetic debugger definitions
  x86/kvm/hyper-v: Add support for synthetic debugger capability
  x86/kvm/hyper-v: enable hypercalls without hypercall page with syndbg
  x86/kvm/hyper-v: Add support for synthetic debugger via hypercalls

 Documentation/virt/kvm/api.rst     |  18 +++
 arch/x86/include/asm/hyperv-tlfs.h |   6 +
 arch/x86/include/asm/kvm_host.h    |  14 +++
 arch/x86/kvm/hyperv.c              | 179 ++++++++++++++++++++++++++++-
 arch/x86/kvm/hyperv.h              |  33 ++++++
 arch/x86/kvm/trace.h               |  51 ++++++++
 arch/x86/kvm/x86.c                 |  13 +++
 include/uapi/linux/kvm.h           |  13 +++
 8 files changed, 325 insertions(+), 2 deletions(-)
```
#### [RFC PATCH 00/70 v2] x86: SEV-ES Guest Support
##### From: Joerg Roedel <joro@8bytes.org>

```c
From patchwork Thu Mar 19 09:12:57 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joerg Roedel <joro@8bytes.org>
X-Patchwork-Id: 11446895
Return-Path: <SRS0=MMtT=5E=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B598214B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Mar 2020 09:20:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9000620722
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Mar 2020 09:20:57 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727053AbgCSJOT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 19 Mar 2020 05:14:19 -0400
Received: from 8bytes.org ([81.169.241.247]:51840 "EHLO theia.8bytes.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727060AbgCSJOS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 19 Mar 2020 05:14:18 -0400
Received: by theia.8bytes.org (Postfix, from userid 1000)
        id C980311D; Thu, 19 Mar 2020 10:14:15 +0100 (CET)
From: Joerg Roedel <joro@8bytes.org>
To: x86@kernel.org
Cc: hpa@zytor.com, Andy Lutomirski <luto@kernel.org>,
        Dave Hansen <dave.hansen@linux.intel.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Thomas Hellstrom <thellstrom@vmware.com>,
        Jiri Slaby <jslaby@suse.cz>,
        Dan Williams <dan.j.williams@intel.com>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Juergen Gross <jgross@suse.com>,
        Kees Cook <keescook@chromium.org>,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org,
        Joerg Roedel <joro@8bytes.org>, Joerg Roedel <jroedel@suse.de>
Subject: [RFC PATCH 00/70 v2] x86: SEV-ES Guest Support
Date: Thu, 19 Mar 2020 10:12:57 +0100
Message-Id: <20200319091407.1481-1-joro@8bytes.org>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

here is an updated version of the patch-set to enable Linux to run as a
guest in an SEV-ES enabled Hypervisor. The first version can be found
here:

	https://lore.kernel.org/lkml/20200211135256.24617-1-joro@8bytes.org/

The first post also includes a more elaborate description of the
implementation requirements and details.  A branch containing these
patches is here:

	https://git.kernel.org/pub/scm/linux/kernel/git/joro/linux.git/log/?h=sev-es-client-v5.6-rc6

There are lots of small changes since the first version, here is a list
of the major ones, which address most of the valuable review comments I
received, thanks for that!

Changes since v1:

	- Rebased to v5.6-rc6

	- Factored out instruction decoding part of the UMIP handler and
	  re-used it in the SEV-ES code.

	- Several enhancements of the instruction decoder as needed by
	  SEV-ES

	- The instruction fetch and memory access code for instruction
	  emulation now handles different user execution modes as well
	  as segment bases.

	- Added emulation of (REP) MOVS instructions

	- Added handling for nesting #VC handlers - which fixed the NMI
	  issues.

	- Pass error_code as a parameter to the #VC exception handlers

	- Reworked early exception dispatch function

	- Moved the GHCB pages out of the per-cpu areas and only
	  allocate them when they are actually needed. The per-cpu areas
	  only store a pointer now.

	- Removed emulation for INVD, now it will just cause an error if
	  used.

	- Added prefixes to the function names.

	- Fixed a bug which broke bare-metal boot with mem_encrypt=on

The last missing change I have on my list is to rework the NMI handling
patch. I decided to postpone this until Thomas' Gleixners rework of the
x86 entry code is ready and merged, because the NMI handling will
conflict with these changes.

Please review.

Thanks,

	Joerg

Doug Covelli (1):
  x86/vmware: Add VMware specific handling for VMMCALL under SEV-ES

Joerg Roedel (51):
  KVM: SVM: Add GHCB Accessor functions
  x86/traps: Move some definitions to <asm/trap_defs.h>
  x86/insn: Make inat-tables.c suitable for pre-decompression code
  x86/umip: Factor out instruction fetch
  x86/umip: Factor out instruction decoding
  x86/insn: Add insn_get_modrm_reg_off()
  x86/insn: Add insn_rep_prefix() helper
  x86/boot/compressed: Fix debug_puthex() parameter type
  x86/boot/compressed/64: Disable red-zone usage
  x86/boot/compressed/64: Add IDT Infrastructure
  x86/boot/compressed/64: Rename kaslr_64.c to ident_map_64.c
  x86/boot/compressed/64: Add page-fault handler
  x86/boot/compressed/64: Always switch to own page-table
  x86/boot/compressed/64: Don't pre-map memory in KASLR code
  x86/boot/compressed/64: Change add_identity_map() to take start and
    end
  x86/boot/compressed/64: Add stage1 #VC handler
  x86/boot/compressed/64: Call set_sev_encryption_mask earlier
  x86/boot/compressed/64: Check return value of
    kernel_ident_mapping_init()
  x86/boot/compressed/64: Add function to map a page unencrypted
  x86/boot/compressed/64: Setup GHCB Based VC Exception handler
  x86/fpu: Move xgetbv()/xsetbv() into separate header
  x86/idt: Move IDT to data segment
  x86/idt: Split idt_data setup out of set_intr_gate()
  x86/idt: Move two function from k/idt.c to i/a/desc.h
  x86/head/64: Install boot GDT
  x86/head/64: Reload GDT after switch to virtual addresses
  x86/head/64: Load segment registers earlier
  x86/head/64: Switch to initial stack earlier
  x86/head/64: Build k/head64.c with -fno-stack-protector
  x86/head/64: Load IDT earlier
  x86/head/64: Move early exception dispatch to C code
  x86/sev-es: Add SEV-ES Feature Detection
  x86/sev-es: Compile early handler code into kernel image
  x86/sev-es: Setup early #VC handler
  x86/sev-es: Setup GHCB based boot #VC handler
  x86/sev-es: Support nested #VC exceptions
  x86/sev-es: Wire up existing #VC exit-code handlers
  x86/sev-es: Handle instruction fetches from user-space
  x86/sev-es: Harden runtime #VC handler for exceptions from user-space
  x86/sev-es: Filter exceptions not supported from user-space
  x86/sev-es: Handle MMIO String Instructions
  x86/sev-es: Handle RDTSCP Events
  x86/sev-es: Handle #AC Events
  x86/sev-es: Handle #DB Events
  x86/paravirt: Allow hypervisor specific VMMCALL handling under SEV-ES
  x86/realmode: Add SEV-ES specific trampoline entry point
  x86/head/64: Don't call verify_cpu() on starting APs
  x86/head/64: Rename start_cpu0
  x86/sev-es: Support CPU offline/online
  x86/cpufeature: Add SEV_ES_GUEST CPU Feature
  x86/sev-es: Add NMI state tracking

Tom Lendacky (18):
  KVM: SVM: Add GHCB definitions
  x86/cpufeatures: Add SEV-ES CPU feature
  x86/sev-es: Add support for handling IOIO exceptions
  x86/sev-es: Add CPUID handling to #VC handler
  x86/sev-es: Setup per-cpu GHCBs for the runtime handler
  x86/sev-es: Add Runtime #VC Exception Handler
  x86/sev-es: Handle MMIO events
  x86/sev-es: Handle MSR events
  x86/sev-es: Handle DR7 read/write events
  x86/sev-es: Handle WBINVD Events
  x86/sev-es: Handle RDTSC Events
  x86/sev-es: Handle RDPMC Events
  x86/sev-es: Handle INVD Events
  x86/sev-es: Handle MONITOR/MONITORX Events
  x86/sev-es: Handle MWAIT/MWAITX Events
  x86/sev-es: Handle VMMCALL Events
  x86/kvm: Add KVM specific VMMCALL handling under SEV-ES
  x86/realmode: Setup AP jump table

 arch/x86/Kconfig                           |    1 +
 arch/x86/boot/Makefile                     |    2 +-
 arch/x86/boot/compressed/Makefile          |    8 +-
 arch/x86/boot/compressed/head_64.S         |   41 +
 arch/x86/boot/compressed/ident_map_64.c    |  320 ++++++
 arch/x86/boot/compressed/idt_64.c          |   53 +
 arch/x86/boot/compressed/idt_handlers_64.S |   82 ++
 arch/x86/boot/compressed/kaslr.c           |   36 +-
 arch/x86/boot/compressed/kaslr_64.c        |  153 ---
 arch/x86/boot/compressed/misc.h            |   34 +-
 arch/x86/boot/compressed/sev-es.c          |  177 +++
 arch/x86/entry/entry_64.S                  |   52 +
 arch/x86/include/asm/cpu.h                 |    2 +-
 arch/x86/include/asm/cpufeatures.h         |    2 +
 arch/x86/include/asm/desc.h                |   28 +
 arch/x86/include/asm/desc_defs.h           |   10 +
 arch/x86/include/asm/fpu/internal.h        |   29 +-
 arch/x86/include/asm/fpu/xcr.h             |   32 +
 arch/x86/include/asm/insn-eval.h           |    6 +
 arch/x86/include/asm/mem_encrypt.h         |    5 +
 arch/x86/include/asm/msr-index.h           |    3 +
 arch/x86/include/asm/pgtable.h             |    2 +-
 arch/x86/include/asm/processor.h           |    1 +
 arch/x86/include/asm/realmode.h            |    4 +
 arch/x86/include/asm/segment.h             |    2 +-
 arch/x86/include/asm/setup.h               |    1 -
 arch/x86/include/asm/sev-es.h              |  119 ++
 arch/x86/include/asm/svm.h                 |  103 ++
 arch/x86/include/asm/trap_defs.h           |   50 +
 arch/x86/include/asm/traps.h               |   51 +-
 arch/x86/include/asm/x86_init.h            |   16 +-
 arch/x86/include/uapi/asm/svm.h            |   11 +
 arch/x86/kernel/Makefile                   |    5 +
 arch/x86/kernel/cpu/amd.c                  |    9 +-
 arch/x86/kernel/cpu/scattered.c            |    1 +
 arch/x86/kernel/cpu/vmware.c               |   50 +-
 arch/x86/kernel/head64.c                   |   57 +-
 arch/x86/kernel/head_32.S                  |    4 +-
 arch/x86/kernel/head_64.S                  |  169 ++-
 arch/x86/kernel/idt.c                      |   52 +-
 arch/x86/kernel/kvm.c                      |   35 +-
 arch/x86/kernel/nmi.c                      |    8 +
 arch/x86/kernel/sev-es-shared.c            |  444 ++++++++
 arch/x86/kernel/sev-es.c                   | 1165 ++++++++++++++++++++
 arch/x86/kernel/smpboot.c                  |    4 +-
 arch/x86/kernel/traps.c                    |    3 +
 arch/x86/kernel/umip.c                     |   49 +-
 arch/x86/lib/insn-eval.c                   |  130 +++
 arch/x86/mm/extable.c                      |    1 +
 arch/x86/mm/mem_encrypt.c                  |   11 +-
 arch/x86/mm/mem_encrypt_identity.c         |    3 +
 arch/x86/realmode/init.c                   |   12 +
 arch/x86/realmode/rm/header.S              |    3 +
 arch/x86/realmode/rm/trampoline_64.S       |   20 +
 arch/x86/tools/gen-insn-attr-x86.awk       |   50 +-
 tools/arch/x86/tools/gen-insn-attr-x86.awk |   50 +-
 56 files changed, 3352 insertions(+), 419 deletions(-)
 create mode 100644 arch/x86/boot/compressed/ident_map_64.c
 create mode 100644 arch/x86/boot/compressed/idt_64.c
 create mode 100644 arch/x86/boot/compressed/idt_handlers_64.S
 delete mode 100644 arch/x86/boot/compressed/kaslr_64.c
 create mode 100644 arch/x86/boot/compressed/sev-es.c
 create mode 100644 arch/x86/include/asm/fpu/xcr.h
 create mode 100644 arch/x86/include/asm/sev-es.h
 create mode 100644 arch/x86/include/asm/trap_defs.h
 create mode 100644 arch/x86/kernel/sev-es-shared.c
 create mode 100644 arch/x86/kernel/sev-es.c
```
#### [PATCH v15 Kernel 0/7] KABIs to support migration for VFIO devices
##### From: Kirti Wankhede <kwankhede@nvidia.com>

```c
From patchwork Thu Mar 19 20:16:37 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kirti Wankhede <kwankhede@nvidia.com>
X-Patchwork-Id: 11448033
Return-Path: <SRS0=MMtT=5E=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 18FCC1874
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Mar 2020 20:50:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E283F20786
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Mar 2020 20:50:19 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="RJ0LiRwA"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727138AbgCSUuT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 19 Mar 2020 16:50:19 -0400
Received: from hqnvemgate26.nvidia.com ([216.228.121.65]:16396 "EHLO
        hqnvemgate26.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725787AbgCSUuS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 19 Mar 2020 16:50:18 -0400
Received: from hqpgpgate101.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate26.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5e73daf90000>; Thu, 19 Mar 2020 13:50:01 -0700
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate101.nvidia.com (PGP Universal service);
  Thu, 19 Mar 2020 13:50:14 -0700
X-PGP-Universal: processed;
        by hqpgpgate101.nvidia.com on Thu, 19 Mar 2020 13:50:14 -0700
Received: from HQMAIL105.nvidia.com (172.20.187.12) by HQMAIL109.nvidia.com
 (172.20.187.15) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Thu, 19 Mar
 2020 20:50:13 +0000
Received: from kwankhede-dev.nvidia.com (10.124.1.5) by HQMAIL105.nvidia.com
 (172.20.187.12) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Thu, 19 Mar 2020 20:50:07 +0000
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
Subject: [PATCH v15 Kernel 0/7] KABIs to support migration for VFIO devices
Date: Fri, 20 Mar 2020 01:46:37 +0530
Message-ID: <1584649004-8285-1-git-send-email-kwankhede@nvidia.com>
X-Mailer: git-send-email 2.7.0
X-NVConfidentiality: public
MIME-Version: 1.0
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1584651001; bh=VPALxdQ6lnCG8+5n/cJsaP3BL+Cr7DxYJrVYSAmCT+k=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         X-NVConfidentiality:MIME-Version:Content-Type;
        b=RJ0LiRwAN3zuDL0EjL37WQW3Z+rvUbB6B55bDQ12LcymtQ/aFVz5N+u0nAnt1TyzC
         LlYnnnok3sYlhxf48YOb6zrwFfTHvwKtqdL0uGM4DcmeNvxp65hytT1ri+Cx3pJ3ve
         MZbSvSkBzyMrBHrPdiZh6nhrD1+ebtW6T8Ih6bqhN3GyDraSSsDw/e9gsDGzSWnPY6
         VMRXRIIVWWLv/wB4ZTMnJhRXR/dxaoIwR8aeLRXhmc1w8902jPuzNqZcC+xUohy5NG
         p0Rs7xCYEHqtAJSxp/RFtqT9cNjzVpnGJAAAFe96WlN9C78YR38QyQIWeTaTwZekc/
         7rKTc3Y7WOKqw==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

This patch set adds:
* New IOCTL VFIO_IOMMU_DIRTY_PAGES to get dirty pages bitmap with
  respect to IOMMU container rather than per device. All pages pinned by
  vendor driver through vfio_pin_pages external API has to be marked as
  dirty during  migration. When IOMMU capable device is present in the
  container and all pages are pinned and mapped, then all pages are marked
  dirty.
  When there are CPU writes, CPU dirty page tracking can identify dirtied
  pages, but any page pinned by vendor driver can also be written by
  device. As of now there is no device which has hardware support for
  dirty page tracking. So all pages which are pinned should be considered
  as dirty.
  This ioctl is also used to start/stop dirty pages tracking for pinned and
  unpinned pages while migration is active.

* Updated IOCTL VFIO_IOMMU_UNMAP_DMA to get dirty pages bitmap before
  unmapping IO virtual address range.
  With vIOMMU, during pre-copy phase of migration, while CPUs are still
  running, IO virtual address unmap can happen while device still keeping
  reference of guest pfns. Those pages should be reported as dirty before
  unmap, so that VFIO user space application can copy content of those
  pages from source to destination.

* Patch 7 detect if IOMMU capable device driver is smart to report pages
  to be marked dirty by pinning pages using vfio_pin_pages() API.


Yet TODO:
Since there is no device which has hardware support for system memmory
dirty bitmap tracking, right now there is no other API from vendor driver
to VFIO IOMMU module to report dirty pages. In future, when such hardware
support will be implemented, an API will be required such that vendor
driver could report dirty pages to VFIO module during migration phases.

Adding revision history from previous QEMU patch set to understand KABI
changes done till now

v14 -> v15
- Minor edits and nit picks.
- In the verification of user allocated bitmap memory, added check of
   maximum size.
- Patches are on tag: next-20200318 and 1-3 patches from Yan's series
  https://lkml.org/lkml/2020/3/12/1255

v13 -> v14
- Added struct vfio_bitmap to kabi. updated structure
  vfio_iommu_type1_dirty_bitmap_get and vfio_iommu_type1_dma_unmap.
- All small changes suggested by Alex.
- Patches are on tag: next-20200318 and 1-3 patches from Yan's series
  https://lkml.org/lkml/2020/3/12/1255

v12 -> v13
- Changed bitmap allocation in vfio_iommu_type1 to per vfio_dma
- Changed VFIO_IOMMU_DIRTY_PAGES ioctl behaviour to be per vfio_dma range.
- Changed vfio_iommu_type1_dirty_bitmap structure to have separate data
  field.

v11 -> v12
- Changed bitmap allocation in vfio_iommu_type1.
- Remove atomicity of ref_count.
- Updated comments for migration device state structure about error
  reporting.
- Nit picks from v11 reviews

v10 -> v11
- Fix pin pages API to free vpfn if it is marked as unpinned tracking page.
- Added proposal to detect if IOMMU capable device calls external pin pages
  API to mark pages dirty.
- Nit picks from v10 reviews

v9 -> v10:
- Updated existing VFIO_IOMMU_UNMAP_DMA ioctl to get dirty pages bitmap
  during unmap while migration is active
- Added flag in VFIO_IOMMU_GET_INFO to indicate driver support dirty page
  tracking.
- If iommu_mapped, mark all pages dirty.
- Added unpinned pages tracking while migration is active.
- Updated comments for migration device state structure with bit
  combination table and state transition details.

v8 -> v9:
- Split patch set in 2 sets, Kernel and QEMU.
- Dirty pages bitmap is queried from IOMMU container rather than from
  vendor driver for per device. Added 2 ioctls to achieve this.

v7 -> v8:
- Updated comments for KABI
- Added BAR address validation check during PCI device's config space load
  as suggested by Dr. David Alan Gilbert.
- Changed vfio_migration_set_state() to set or clear device state flags.
- Some nit fixes.

v6 -> v7:
- Fix build failures.

v5 -> v6:
- Fix build failure.

v4 -> v5:
- Added decriptive comment about the sequence of access of members of
  structure vfio_device_migration_info to be followed based on Alex's
  suggestion
- Updated get dirty pages sequence.
- As per Cornelia Huck's suggestion, added callbacks to VFIODeviceOps to
  get_object, save_config and load_config.
- Fixed multiple nit picks.
- Tested live migration with multiple vfio device assigned to a VM.

v3 -> v4:
- Added one more bit for _RESUMING flag to be set explicitly.
- data_offset field is read-only for user space application.
- data_size is read for every iteration before reading data from migration,
  that is removed assumption that data will be till end of migration
  region.
- If vendor driver supports mappable sparsed region, map those region
  during setup state of save/load, similarly unmap those from cleanup
  routines.
- Handles race condition that causes data corruption in migration region
  during save device state by adding mutex and serialiaing save_buffer and
  get_dirty_pages routines.
- Skip called get_dirty_pages routine for mapped MMIO region of device.
- Added trace events.
- Split into multiple functional patches.

v2 -> v3:
- Removed enum of VFIO device states. Defined VFIO device state with 2
  bits.
- Re-structured vfio_device_migration_info to keep it minimal and defined
  action on read and write access on its members.

v1 -> v2:
- Defined MIGRATION region type and sub-type which should be used with
  region type capability.
- Re-structured vfio_device_migration_info. This structure will be placed
  at 0th offset of migration region.
- Replaced ioctl with read/write for trapped part of migration region.
- Added both type of access support, trapped or mmapped, for data section
  of the region.
- Moved PCI device functions to pci file.
- Added iteration to get dirty page bitmap until bitmap for all requested
  pages are copied.

Thanks,
Kirti



Kirti Wankhede (7):
  vfio: KABI for migration interface for device state
  vfio iommu: Remove atomicity of ref_count of pinned pages
  vfio iommu: Add ioctl definition for dirty pages tracking.
  vfio iommu: Implementation of ioctl for dirty pages tracking.
  vfio iommu: Update UNMAP_DMA ioctl to get dirty bitmap before unmap
  vfio iommu: Adds flag to indicate dirty pages tracking capability
    support
  vfio: Selective dirty page tracking if IOMMU backed device pins pages

 drivers/vfio/vfio.c             |  13 +-
 drivers/vfio/vfio_iommu_type1.c | 398 ++++++++++++++++++++++++++++++++++++++--
 include/linux/vfio.h            |   4 +-
 include/uapi/linux/vfio.h       | 297 +++++++++++++++++++++++++++++-
 4 files changed, 690 insertions(+), 22 deletions(-)
```
