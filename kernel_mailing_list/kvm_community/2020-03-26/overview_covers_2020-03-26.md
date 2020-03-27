

#### [PATCH 0/3] KVM: X86: Single target IPI fastpath enhancement 
##### From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>

```c
From patchwork Thu Mar 26 02:19:59 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11458989
Return-Path: <SRS0=eSA5=5L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 077FE81
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Mar 2020 02:20:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id DB87020772
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Mar 2020 02:20:17 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="c6UAd3xF"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727706AbgCZCUP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 25 Mar 2020 22:20:15 -0400
Received: from mail-pf1-f195.google.com ([209.85.210.195]:41192 "EHLO
        mail-pf1-f195.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727575AbgCZCUO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 25 Mar 2020 22:20:14 -0400
Received: by mail-pf1-f195.google.com with SMTP id z65so2017765pfz.8;
        Wed, 25 Mar 2020 19:20:14 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=JT7flklXnR9y13ubSQU0XF0F5XqUE8uC8TpkRKKiqsw=;
        b=c6UAd3xFeyAjUUmmzvO4WGQgXQua4ldyW9QU+tclp4D7MCELOPbywWJuMoY9Y4tyJU
         Fw07JwnKJeMyetrfHMxnG+VEZG6m5BeMAmWuuiyNZ2A8UQLdcwBZnhIzsy3U9Dc4MBue
         h/KyE2EPUn+UCmVDqVNvBrKvZn7ndRSkkXopoqYmThPX5wwPmBxmHcI1rnvw5u0D9tZt
         T1OTQ9XZndCBp4BaF7xzpGayKaRAkwlaOpxdfKvjquxMjSxJLvP6wQ+xFLiOrL7xIBi7
         lJUV2+WAktRs0dorfqsprEArlRBao1sTI+kDnPtRxFxWvSMEsanRdrnUuUvmUpkxRZ/a
         Wqbg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=JT7flklXnR9y13ubSQU0XF0F5XqUE8uC8TpkRKKiqsw=;
        b=Hps3wjIYxBdGArotv6qwpERbKXiDQ7V6K8pKJviGeItsqvzyK/+lU6X8GV0wd/Es9x
         mDxjMnWiM3pYxT8qVuAXwAqLlYToNNe7WY3UuozKoIV5tO3Pm6zayHAb1uUkmimUBtlo
         R5RWe5MshPpmWAfx1O+ZP8BQFLzqPijCXdSzXTbZRkyNoTAXk6H4GTWjmol/yDBQoZPt
         5OppJ3h54oe++ggU19o9geW/jJd7nbGNRfv7cuT8EfIQwr9VvSOK5SGT6XB526oa/uX8
         SG5ydYZESKvdZAWdPB7STULwwyzy1Yuun91SIwGdfV/LDeJO1p+5zjYlMHeKaIkL9g/U
         fkEQ==
X-Gm-Message-State: ANhLgQ1HwDgNseKSc99oCF82aocGiflgVoEuIgqBOIa6bNVZfCo4Okes
        mfr09EzXPNKo5DtU0UpK1X8wC9yw
X-Google-Smtp-Source: 
 ADFU+vvvdmFKfJ9kw1Zhagg2kWtFubF0zTbVzMrj9gWMRdEFRNeF+APUerHkEToqK6BiKZWaTdoqYQ==
X-Received: by 2002:a63:7515:: with SMTP id q21mr4951638pgc.46.1585189213598;
        Wed, 25 Mar 2020 19:20:13 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 mq18sm452975pjb.6.2020.03.25.19.20.11
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-SHA bits=128/128);
        Wed, 25 Mar 2020 19:20:13 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Subject: [PATCH 0/3] KVM: X86: Single target IPI fastpath enhancement 
Date: Thu, 26 Mar 2020 10:19:59 +0800
Message-Id: <1585189202-1708-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The original single target IPI fastpath patch forgot to filter the 
ICR destination shorthand field. Multicast IPI is not suitable for 
this feature since wakeup the multiple sleeping vCPUs will extend 
the interrupt disabled time, it especially worse in the over-subscribe 
and VM has a little bit more vCPUs scenario. Let's narrow it down to 
single target IPI. In addition, this patchset micro-optimize virtual 
IPI emulation sequence for fastpath.

Wanpeng Li (3):
  KVM: X86: Delay read msr data iff writes ICR MSR
  KVM: X86: Narrow down the IPI fastpath to single target IPI
  KVM: X86: Micro-optimize IPI fastpath delay

 arch/x86/kvm/lapic.c |  4 ++--
 arch/x86/kvm/lapic.h |  1 +
 arch/x86/kvm/x86.c   | 14 +++++++++++---
 3 files changed, 14 insertions(+), 5 deletions(-)
```
#### [RFC v3 0/3] Fix errors when try to build kvm selftests on specified
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
From patchwork Thu Mar 26 03:07:47 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11459161
Return-Path: <SRS0=eSA5=5L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 88DCC17EA
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Mar 2020 03:26:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6A34520848
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Mar 2020 03:26:00 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728069AbgCZDZc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 25 Mar 2020 23:25:32 -0400
Received: from mga18.intel.com ([134.134.136.126]:53303 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727639AbgCZDZa (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 25 Mar 2020 23:25:30 -0400
IronPort-SDR: 
 s4UQgJmIejk3VLJLH41WWRqHY0jdBHvZcXuQMm9HI86DWyarjKvVIbWB3R2cF9iRyDytmI2Eoy
 DhUE5XtXE57g==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by orsmga106.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 25 Mar 2020 20:25:29 -0700
IronPort-SDR: 
 TQP58wxqJHStCgf82omJMZzoodNQcpnqWADTBT0t3RDce8k4I2RL+UXv8iUUV8eyogYjZXR+oE
 pJrP3oPHtEYA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,306,1580803200";
   d="scan'208";a="446842797"
Received: from lxy-clx-4s.sh.intel.com ([10.239.43.39])
  by fmsmga005.fm.intel.com with ESMTP; 25 Mar 2020 20:25:27 -0700
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>, Shuah Khan <shuah@kernel.org>
Cc: kvm@vger.kernel.org, linux-kselftest@vger.kernel.org,
        linux-kernel@vger.kernel.org, Xiaoyao Li <xiaoyao.li@intel.com>
Subject: [RFC v3 0/3] Fix errors when try to build kvm selftests on specified
 output
Date: Thu, 26 Mar 2020 11:07:47 +0800
Message-Id: <20200326030750.173972-1-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Shuah,

Hope you're happy with this version that I only touch KVM's Makefile.

I attempted to build KVM selftests on a specified dir, unfortunately
neither	"make O=/path/to/mydir TARGETS=kvm" in tools/testing/selftests, nor
"make OUTPUT=/path/to/mydir" in tools/testing/selftests/kvm work.

This series aims to fix them.

Patch 1 and Patch 3 are the fix patch, please see the seperate for details.
While Patch 2 is more or less an fix for the future issue, since it works
without Patch 2 currently.

Changes in v3:
 - Drop all the patches that touch things out of KVM
 - Create OUTPUT dir in KVM's Makefile
 - Correct the INSTALL_HDR_PATH in KVM's Makefile

Changes in v2:
https://lore.kernel.org/kvm/20200325140133.103236-1-xiaoyao.li@intel.com/
 - fix the no directory issue in lib.mk
 - make kvm fixes seperate patch
 - Add the patch to fix linux src tree not clean issue

v1:
https://lore.kernel.org/kvm/20200315093425.33600-1-xiaoyao.li@intel.com/

Xiaoyao Li (3):
  kvm: selftests: Fix no directory error when OUTPUT specified
  kvm: selftests: Use the right INSTALL_HDR_PATH when OUTPUT specified
    and MAKELEVEL is 0
  kvm: selftests: Fix header path when built from parent level with O
    specified

 tools/testing/selftests/kvm/Makefile | 15 ++++++++++++++-
 1 file changed, 14 insertions(+), 1 deletion(-)
```
#### [PATCH v2 0/2] VFIO mdev aggregated resources handling
##### From: Zhenyu Wang <zhenyuw@linux.intel.com>

```c
From patchwork Thu Mar 26 05:41:34 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhenyu Wang <zhenyuw@linux.intel.com>
X-Patchwork-Id: 11459303
Return-Path: <SRS0=eSA5=5L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 07AC3913
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Mar 2020 05:41:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E506C20772
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Mar 2020 05:41:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725994AbgCZFlj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 26 Mar 2020 01:41:39 -0400
Received: from mga14.intel.com ([192.55.52.115]:26877 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725819AbgCZFlj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 26 Mar 2020 01:41:39 -0400
IronPort-SDR: 
 VkQ2H+db0R4LyOFfZ/soR/arVFijvxviNa7C1ODALIVzDycN8OaFSWC4Wdp2Y2RAu2rLyeX0jm
 rfS87PNPvUkA==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by fmsmga103.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 25 Mar 2020 22:41:39 -0700
IronPort-SDR: 
 wlkSnlxSudaj/8BAa5WVuoRT5YAw4yX+qM4Qc4Rki61dQfKy2m6Fp3S+2CCwZEt9nEh80jYizl
 ImBFeDDycoew==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,307,1580803200";
   d="scan'208";a="393862301"
Received: from zhaji-mobl3.ccr.corp.intel.com (HELO
 dell-xps.ccr.corp.intel.com) ([10.249.174.174])
  by orsmga004.jf.intel.com with ESMTP; 25 Mar 2020 22:41:37 -0700
From: Zhenyu Wang <zhenyuw@linux.intel.com>
To: alex.williamson@redhat.com
Cc: kvm@vger.kernel.org, kevin.tian@intel.com,
        intel-gvt-dev@lists.freedesktop.org
Subject: [PATCH v2 0/2] VFIO mdev aggregated resources handling
Date: Thu, 26 Mar 2020 13:41:34 +0800
Message-Id: <20200326054136.2543-1-zhenyuw@linux.intel.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

This is a refresh on previous series: https://patchwork.kernel.org/cover/11208279/
and https://patchwork.freedesktop.org/series/70425/

Current mdev device create interface depends on fixed mdev type, which
get uuid from user to create instance of mdev device. If user wants to
use customized number of resource for mdev device, then only can
create new mdev type for that which may not be flexible. This
requirement comes not only from to be able to allocate flexible
resources for KVMGT, but also from Intel scalable IO virtualization
which would use vfio/mdev to be able to allocate arbitrary resources
on mdev instance. More info on [1] [2] [3].

As we agreed that for current opaque mdev device type, we'd still
explore management interface based on mdev sysfs definition. And this
one tries to follow Alex's previous suggestion to create generic
parameters under 'mdev' directory for each device, so vendor driver
could provide support like as other defined mdev sysfs entries.

For mdev type with aggregation support, files as "aggregated_instances"
and "max_aggregation" should be created under 'mdev' directory. E.g

/sys/devices/pci0000:00/0000:00:02.0/<UUID>/mdev/
   |-- aggregated_instances
   |-- max_aggregation

"aggregated_instances" is used to set or return current number of
instances for aggregation, which can not be larger than "max_aggregation".

The first patch is to update the document for new mdev parameter directory.
The second one is to add aggregation support in GVT driver.

References:
[1] https://software.intel.com/en-us/download/intel-virtualization-technology-for-directed-io-architecture-specification
[2] https://software.intel.com/en-us/download/intel-scalable-io-virtualization-technical-specification
[3] https://schd.ws/hosted_files/lc32018/00/LC3-SIOV-final.pdf

Zhenyu Wang (2):
  Documentation/driver-api/vfio-mediated-device.rst: update for
    aggregation support
  drm/i915/gvt: mdev aggregation type

 .../driver-api/vfio-mediated-device.rst       |  19 ++
 drivers/gpu/drm/i915/gvt/aperture_gm.c        |  44 +++--
 drivers/gpu/drm/i915/gvt/gtt.c                |   9 +-
 drivers/gpu/drm/i915/gvt/gvt.c                |   7 +-
 drivers/gpu/drm/i915/gvt/gvt.h                |  42 +++--
 drivers/gpu/drm/i915/gvt/kvmgt.c              | 115 +++++++++++-
 drivers/gpu/drm/i915/gvt/vgpu.c               | 172 ++++++++++++------
 7 files changed, 314 insertions(+), 94 deletions(-)
```
#### [PATCH v11 0/9] Introduce support for guest CET feature
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
From patchwork Thu Mar 26 08:18:37 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11459585
Return-Path: <SRS0=eSA5=5L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C261F1668
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Mar 2020 08:16:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A486020772
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Mar 2020 08:16:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727656AbgCZIP7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 26 Mar 2020 04:15:59 -0400
Received: from mga02.intel.com ([134.134.136.20]:27555 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726298AbgCZIP7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 26 Mar 2020 04:15:59 -0400
IronPort-SDR: 
 gETYUXWuPltYKHUr6p9v9L11Zo/TK0QCIxDnf2STY5FmrWkI2Z0W+3CxOSFJocdJKliVRCau93
 qNCd6zs9Nc3Q==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by orsmga101.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 26 Mar 2020 01:15:58 -0700
IronPort-SDR: 
 xk+6ZvxFpr0srCx4pxzWjlrkRVfTarECFniJ5feN/lkD/u/kKDbVGaadgS3ZZvaDdCnfeDvz/O
 wiXc/zX24y+Q==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,307,1580803200";
   d="scan'208";a="393898809"
Received: from local-michael-cet-test.sh.intel.com ([10.239.159.128])
  by orsmga004.jf.intel.com with ESMTP; 26 Mar 2020 01:15:55 -0700
From: Yang Weijiang <weijiang.yang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        pbonzini@redhat.com, sean.j.christopherson@intel.com,
        jmattson@google.com
Cc: yu.c.zhang@linux.intel.com, Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH v11 0/9] Introduce support for guest CET feature
Date: Thu, 26 Mar 2020 16:18:37 +0800
Message-Id: <20200326081847.5870-1-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Control-flow Enforcement Technology (CET) provides protection against
Return/Jump-Oriented Programming (ROP/JOP) attack. It includes two
sub-features: Shadow Stack (SHSTK) and Indirect Branch Tracking (IBT).

KVM needs to update to enable guest CET feature.
This patchset implements CET related CPUID/XSAVES enumeration, MSRs
and vmentry/vmexit configuration etc.so that guest kernel can setup CET
runtime infrastructure based on them. Some CET MSRs and related feature
flags used reference the definitions in kernel patchset.

CET kernel patches are here:
https://lkml.org/lkml/2020/2/5/593
https://lkml.org/lkml/2020/2/5/604

v10 -> v11
- Fixed a guest vmentry failure issue when guest reboots.
- Used vm_xxx_control_{set, clear}bit() to avoid side effect, it'll
  clear cached data instead of pure VMCS field bits.
- Added vcpu->arch.guest_supported_xss dedidated for guest runtime mask,
  this avoids supported_xss overwritten issue caused by an old qemu.
- Separated vmentry/vmexit state setting with CR0/CR4 dependency check
  to make the patch more clear.
- Added CET VMCS states in dump_vmcs() for debugging purpose.
- Other refactor based on testing.
- This patch serial is built on top of below branch and CET kernel patches
  for seeking xsaves support:
  https://git.kernel.org/pub/scm/virt/kvm/kvm.git/log/?h=cpu-caps

v9 -> v10
- Refactored code per Sean's review feedback.
- Added CET support for nested VM.
- Removed fix-patch for CPUID(0xd,N) enumeration as this part is done
  by Paolo and Sean.
- This new patchset is based on Paolo's queued cpu_caps branch.
- Modified patch per XSAVES related change.
- Consolidated KVM unit-test patch with KVM patches.

v8 -> v9:
- Refactored msr-check functions per Sean's feedback.
- Fixed a few issues per Sean's suggestion.
- Rebased patch to kernel-v5.4.
- Moved CET CPUID feature bits and CR4.CET to last patch.

v7 -> v8:
- Addressed Jim and Sean's feedback on: 1) CPUID(0xD,i) enumeration. 2)
  sanity check when configure guest CET. 3) function improvement.
- Added more sanity check functions.
- Set host vmexit default status so that guest won't leak CET status to
  host when vmexit.
- Added CR0.WP vs. CR4.CET mutual constrains.

v6 -> v7:
- Rebased patch to kernel v5.3
- Sean suggested to change CPUID(0xd, n) enumeration code as alined with
  existing one, and I think it's better to make the fix as an independent patch 
  since XSS MSR are being used widely on X86 platforms.
- Check more host and guest status before configure guest CET
  per Sean's feedback.
- Add error-check before guest accesses CET MSRs per Sean's feedback.
- Other minor fixes suggested by Sean.

v5 -> v6:
- Rebase patch to kernel v5.2.
- Move CPUID(0xD, n>=1) helper to a seperate patch.
- Merge xsave size fix with other patch.
- Other minor fixes per community feedback.

v4 -> v5:
- Rebase patch to kernel v5.1.
- Wrap CPUID(0xD, n>=1) code to a helper function.
- Pass through MSR_IA32_PL1_SSP and MSR_IA32_PL2_SSP to Guest.
- Add Co-developed-by expression in patch description.
- Refine patch description.

v3 -> v4:
- Add Sean's patch for loading Guest fpu state before access XSAVES
  managed CET MSRs.
- Melt down CET bits setting into CPUID configuration patch.
- Add VMX interface to query Host XSS.
- Check Host and Guest XSS support bits before set Guest XSS.
- Make Guest SHSTK and IBT feature enabling independent.
- Do not report CET support to Guest when Host CET feature is Disabled.

v2 -> v3:
- Modified patches to make Guest CET independent to Host enabling.
- Added patch 8 to add user space access for Guest CET MSR access.
- Modified code comments and patch description to reflect changes.

v1 -> v2:
- Re-ordered patch sequence, combined one patch.
- Added more description for CET related VMCS fields.
- Added Host CET capability check while enabling Guest CET loading bit.
- Added Host CET capability check while reporting Guest CPUID(EAX=7, EXC=0).
- Modified code in reporting Guest CPUID(EAX=D,ECX>=1), make it clearer.
- Added Host and Guest XSS mask check while setting bits for Guest XSS.



Sean Christopherson (1):
  KVM: X86: Load guest fpu state when access MSRs managed by XSAVES

Yang Weijiang (8):
  KVM: VMX: Introduce CET VMX fields and flags
  KVM: VMX: Set guest CET MSRs per KVM and host configuration
  KVM: VMX: Set host/guest CET states for vmexit/vmentry
  KVM: VMX: Check CET dependencies on CR settings
  KVM: X86: Refresh CPUID once guest XSS MSR changes
  KVM: X86: Add userspace access interface for CET MSRs
  KVM: VMX: Enable CET support for nested VM
  KVM: X86: Set CET feature bits for CPUID enumeration

 arch/x86/include/asm/kvm_host.h |   4 +-
 arch/x86/include/asm/vmx.h      |   8 ++
 arch/x86/include/uapi/asm/kvm.h |   1 +
 arch/x86/kvm/cpuid.c            |  25 +++-
 arch/x86/kvm/vmx/capabilities.h |  10 ++
 arch/x86/kvm/vmx/nested.c       |  41 +++++-
 arch/x86/kvm/vmx/vmcs12.c       |   6 +
 arch/x86/kvm/vmx/vmcs12.h       |  14 +-
 arch/x86/kvm/vmx/vmx.c          | 232 +++++++++++++++++++++++++++++++-
 arch/x86/kvm/x86.c              |  46 ++++++-
 arch/x86/kvm/x86.h              |   2 +-
 11 files changed, 376 insertions(+), 13 deletions(-)
```
#### [PATCH 0/3] KVM: x86: sync SPTEs on page/EPT fault injection
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From patchwork Thu Mar 26 09:35:13 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11459739
Return-Path: <SRS0=eSA5=5L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5C1B1161F
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Mar 2020 09:35:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3C89420748
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Mar 2020 09:35:22 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="gE1vAYe7"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727854AbgCZJfV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 26 Mar 2020 05:35:21 -0400
Received: from us-smtp-delivery-74.mimecast.com ([63.128.21.74]:57338 "EHLO
        us-smtp-delivery-74.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726540AbgCZJfV (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 26 Mar 2020 05:35:21 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1585215320;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=mHAcO/esGjuXCW34/CgY8eM7k2k6/5G4mIqIMAwoOLc=;
        b=gE1vAYe7wK+kZ457Ib0lsYm57apQEoNqzD1Ix0rkfa3EHopQrzIA3Tl+VaSuqJvRF3X5x/
        v2I3DeC7SCTSvUDXayW/cna8p8Ss4poDaMM+HUgZL3emMpxKqXNPSN9/BTn9Avq73VF3jP
        en7fnrKJNAKchyiSzw1EsI7h1Qk2flY=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-480-U5kOa6KsMQy72PQznZ-5Kg-1; Thu, 26 Mar 2020 05:35:18 -0400
X-MC-Unique: U5kOa6KsMQy72PQznZ-5Kg-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id A9ABB801E53;
        Thu, 26 Mar 2020 09:35:17 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id EA7A49CA3;
        Thu, 26 Mar 2020 09:35:16 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Junaid Shahid <junaids@google.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>
Subject: [PATCH 0/3] KVM: x86: sync SPTEs on page/EPT fault injection
Date: Thu, 26 Mar 2020 05:35:13 -0400
Message-Id: <20200326093516.24215-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is my take on Junaid and Sean's patch, from the TLB cleanup series.
It passes initial tests, including my usual guest installation and
kvm-unit-tests battery (with both ept=0 and ept=1), but I'm not sure if
there's anything that isn't covered by kvm-unit-tests, especially for
nested.  I have not yet run guest installation tests under nested
virt but I will before merging the whole TLB cleanup series.

Please review!

Junaid Shahid (1):
  KVM: x86: Sync SPTEs when injecting page/EPT fault into L1

Paolo Bonzini (2):
  KVM: x86: introduce kvm_mmu_invalidate_gva
  KVM: x86: cleanup kvm_inject_emulated_page_fault

 arch/x86/include/asm/kvm_host.h |  2 +
 arch/x86/kvm/mmu/mmu.c          | 77 +++++++++++++++++++--------------
 arch/x86/kvm/mmu/paging_tmpl.h  |  2 +-
 arch/x86/kvm/vmx/nested.c       | 12 ++---
 arch/x86/kvm/vmx/vmx.c          |  2 +-
 arch/x86/kvm/x86.c              | 16 +++++--
 6 files changed, 67 insertions(+), 44 deletions(-)
```
#### [PATCH V9 0/9] vDPA support
##### From: Jason Wang <jasowang@redhat.com>

```c
From patchwork Thu Mar 26 14:01:16 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11460171
Return-Path: <SRS0=eSA5=5L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4651E6CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Mar 2020 14:02:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 16C9B2076A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Mar 2020 14:02:40 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="hFKQXPT/"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728000AbgCZOCd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 26 Mar 2020 10:02:33 -0400
Received: from us-smtp-delivery-74.mimecast.com ([216.205.24.74]:23526 "EHLO
        us-smtp-delivery-74.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727652AbgCZOCd (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 26 Mar 2020 10:02:33 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1585231352;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=hlxFFWslsjTIeOh65U/fkAb5jyciCQRgHFLi5X0yXEg=;
        b=hFKQXPT/YUd8BaKLcrZN3mRQRG/2+uwFEBDQVT16YxZj0iZxfI2ojbXjFHchfE3bfAKjvN
        wUIPTipKIRPzXuWOskwaltFAu3S3IeK6RgbS5FX5TabK4JbYUaG16TILwWTOXfAod7RHZN
        ICafM5O7N9hY0Y81K7qZhdegqSVanE4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-379-uUgACe8UP5CiCYTA-MR9Pw-1; Thu, 26 Mar 2020 10:02:02 -0400
X-MC-Unique: uUgACe8UP5CiCYTA-MR9Pw-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 1AD841926DA0;
        Thu, 26 Mar 2020 14:01:59 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-12-19.pek2.redhat.com [10.72.12.19])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 7944A60C80;
        Thu, 26 Mar 2020 14:01:27 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: mst@redhat.com, linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org
Cc: jgg@mellanox.com, maxime.coquelin@redhat.com,
        cunming.liang@intel.com, zhihong.wang@intel.com,
        rob.miller@broadcom.com, xiao.w.wang@intel.com,
        lingshan.zhu@intel.com, eperezma@redhat.com, lulu@redhat.com,
        parav@mellanox.com, kevin.tian@intel.com, stefanha@redhat.com,
        rdunlap@infradead.org, hch@infradead.org, aadam@redhat.com,
        jiri@mellanox.com, shahafs@mellanox.com, hanand@xilinx.com,
        mhabets@solarflare.com, gdawar@xilinx.com, saugatm@xilinx.com,
        vmireyno@marvell.com, zhangweining@ruijie.com.cn,
        Jason Wang <jasowang@redhat.com>
Subject: [PATCH V9 0/9] vDPA support
Date: Thu, 26 Mar 2020 22:01:16 +0800
Message-Id: <20200326140125.19794-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all:

This is an update version of vDPA support in kernel.

vDPA device is a device that uses a datapath which complies with the
virtio specifications with vendor specific control path. vDPA devices
can be both physically located on the hardware or emulated by
software. vDPA hardware devices are usually implemented through PCIE
with the following types:

- PF (Physical Function) - A single Physical Function
- VF (Virtual Function) - Device that supports single root I/O
  virtualization (SR-IOV). Its Virtual Function (VF) represents a
  virtualized instance of the device that can be assigned to different
  partitions
- ADI (Assignable Device Interface) and its equivalents - With
  technologies such as Intel Scalable IOV, a virtual device (VDEV)
  composed by host OS utilizing one or more ADIs. Or its equivalent
  like SF (Sub function) from Mellanox.

From a driver's perspective, depends on how and where the DMA
translation is done, vDPA devices are split into two types:

- Platform specific DMA translation - From the driver's perspective,
  the device can be used on a platform where device access to data in
  memory is limited and/or translated. An example is a PCIE vDPA whose
  DMA request was tagged via a bus (e.g PCIE) specific way. DMA
  translation and protection are done at PCIE bus IOMMU level.
- Device specific DMA translation - The device implements DMA
  isolation and protection through its own logic. An example is a vDPA
  device which uses on-chip IOMMU.

To hide the differences and complexity of the above types for a vDPA
device/IOMMU options and in order to present a generic virtio device
to the upper layer, a device agnostic framework is required.

This series introduces a software vDPA bus which abstracts the
common attributes of vDPA device, vDPA bus driver and the
communication method, the bus operations (vdpa_config_ops) between the
vDPA device abstraction and the vDPA bus driver. This allows multiple
types of drivers to be used for vDPA device like the virtio_vdpa and
vhost_vdpa driver to operate on the bus and allow vDPA device could be
used by either kernel virtio driver or userspace vhost drivers as:

   virtio drivers  vhost drivers
          |             |
    [virtio bus]   [vhost uAPI]
          |             |
   virtio device   vhost device
   virtio_vdpa drv vhost_vdpa drv
             \       /
            [vDPA bus]
                 |
            vDPA device
            hardware drv
                 |
            [hardware bus]
                 |
            vDPA hardware

virtio_vdpa driver is a transport implementation for kernel virtio
drivers on top of vDPA bus operations. An alternative is to refactor
virtio bus which is sub-optimal since the bus and drivers are designed
to be use by kernel subsystem, a non-trivial major refactoring is
needed which may impact a brunches of drivers and devices
implementation inside the kernel. Using a new transport may grealy
simply both the design and changes.

vhost_vdpa driver is a new type of vhost device which allows userspace
vhost drivers to use vDPA devices via vhost uAPI (with minor
extension). This help to minimize the changes of existed vhost drivers
for using vDPA devices.

With the abstraction of vDPA bus and vDPA bus operations, the
difference and complexity of the under layer hardware is hidden from
upper layer. The vDPA bus drivers on top can use a unified
vdpa_config_ops to control different types of vDPA device.

Two drivers were implemented with the framework introduced in this
series:

- Intel IFC VF driver which depends on the platform IOMMU for DMA
  translation
- VDPA simulator which is a software test device with an emulated
  onchip IOMMU

Future work:

- direct doorbell mapping support
- control virtqueue support
- dirty page tracking support
- direct interrupt support
- management API (devlink)

Please review.

Thanks

Changes from V8:

- switch to use devres for PCI resoureces of IFCVF (Jason)
- require the caller of vdap_alloc_device() to use "struct foo"
  instead of foo (Jason)
- some tweaks on the IFCVF driver

Changes from V7:

- refine kconfig to solve the dependency issues on archs that lacks of
  CONFIG_VIRTUALIZATION (kbuild)

Changes from V6:

- vdpa_alloc_device() will allocate parent strcture (Jason)
- remove the vdpa core dev info in IFCVF patch (Jason)
- provide a free method in the vdpa bus operations for drivet to free
  private data
- switch to use new layout in vdapsim and IFCVF
- make IFCVF depends on PCI_MSI (kbuild)
- some tweaks on the IFCVF driver

Changes from V5:

- include Intel IFCVF driver and vhost-vdpa drivers
- add the platform IOMMU support for vhost-vdpa
- check the return value of dev_set_name() (Jason)
- various tweaks and fixes

Changes from V4:

- use put_device() instead of kfree when fail to register virtio
  device (Jason)
- simplify the error handling when allocating vdpasim device (Jason)
- don't use device_for_each_child() during module exit (Jason)
- correct the error checking for vdpa_alloc_device() (Harpreet, Lingshan)

Changes from V3:

- various Kconfig fixes (Randy)

Changes from V2:

- release idr in the release function for put_device() unwind (Jason)
- don't panic when fail to register vdpa bus (Jason)
- use unsigned int instead of int for ida (Jason)
- fix the wrong commit log in virito_vdpa patches (Jason)
- make vdpa_sim depends on RUNTIME_TESTING_MENU (Michael)
- provide a bus release function for vDPA device (Jason)
- fix the wrong unwind when creating devices for vDPA simulator (Jason)
- move vDPA simulator to a dedicated directory (Lingshan)
- cancel the work before release vDPA simulator

Changes from V1:

- drop sysfs API, leave the management interface to future development
  (Michael)
- introduce incremental DMA ops (dma_map/dma_unmap) (Michael)
- introduce dma_device and use it instead of parent device for doing
  IOMMU or DMA from bus driver (Michael, Jason, Ling Shan, Tiwei)
- accept parent device and dma device when register vdpa device
- coding style and compile fixes (Randy)
- using vdpa_xxx instead of xxx_vdpa (Jason)
- ove vDPA accessors to header and make it static inline (Jason)
- split vdp_register_device() into two helpers vdpa_init_device() and
  vdpa_register_device() which allows intermediate step to be done (Jason)
- warn on invalidate queue state when fail to creating virtqueue (Jason)
- make to_virtio_vdpa_device() static (Jason)
- use kmalloc/kfree instead of devres for virtio vdpa device (Jason)
- avoid using cast in vdpa bus function (Jason)
- introduce module_vdpa_driver and fix module refcnt (Jason)
- fix returning freed address in vdapsim coherent DMA addr allocation (Dan)
- various other fixes and tweaks

V8: https://lkml.org/lkml/2020/3/25/125
V7: https://lkml.org/lkml/2020/3/24/21
V6: https://lkml.org/lkml/2020/3/18/88
V5: https://lkml.org/lkml/2020/2/26/58
V4: https://lkml.org/lkml/2020/2/20/59
V3: https://lkml.org/lkml/2020/2/19/1347
V2: https://lkml.org/lkml/2020/2/9/275
V1: https://lkml.org/lkml/2020/1/16/353

Jason Wang (7):
  vhost: refine vhost and vringh kconfig
  vhost: allow per device message handler
  vhost: factor out IOTLB
  vringh: IOTLB support
  vDPA: introduce vDPA bus
  virtio: introduce a vDPA based transport
  vdpasim: vDPA device simulator

Tiwei Bie (1):
  vhost: introduce vDPA-based backend

Zhu Lingshan (1):
  virtio: Intel IFC VF driver for VDPA

 MAINTAINERS                             |   2 +
 arch/arm/kvm/Kconfig                    |   2 -
 arch/arm64/kvm/Kconfig                  |   2 -
 arch/mips/kvm/Kconfig                   |   2 -
 arch/powerpc/kvm/Kconfig                |   2 -
 arch/s390/kvm/Kconfig                   |   4 -
 arch/x86/kvm/Kconfig                    |   4 -
 drivers/Kconfig                         |   2 +
 drivers/misc/mic/Kconfig                |   4 -
 drivers/net/caif/Kconfig                |   4 -
 drivers/vhost/Kconfig                   |  42 +-
 drivers/vhost/Kconfig.vringh            |   6 -
 drivers/vhost/Makefile                  |   6 +
 drivers/vhost/iotlb.c                   | 177 +++++
 drivers/vhost/net.c                     |   5 +-
 drivers/vhost/scsi.c                    |   2 +-
 drivers/vhost/vdpa.c                    | 883 ++++++++++++++++++++++++
 drivers/vhost/vhost.c                   | 233 +++----
 drivers/vhost/vhost.h                   |  45 +-
 drivers/vhost/vringh.c                  | 421 ++++++++++-
 drivers/vhost/vsock.c                   |   2 +-
 drivers/virtio/Kconfig                  |  15 +
 drivers/virtio/Makefile                 |   2 +
 drivers/virtio/vdpa/Kconfig             |  37 +
 drivers/virtio/vdpa/Makefile            |   4 +
 drivers/virtio/vdpa/ifcvf/Makefile      |   3 +
 drivers/virtio/vdpa/ifcvf/ifcvf_base.c  | 389 +++++++++++
 drivers/virtio/vdpa/ifcvf/ifcvf_base.h  | 118 ++++
 drivers/virtio/vdpa/ifcvf/ifcvf_main.c  | 435 ++++++++++++
 drivers/virtio/vdpa/vdpa.c              | 180 +++++
 drivers/virtio/vdpa/vdpa_sim/Makefile   |   2 +
 drivers/virtio/vdpa/vdpa_sim/vdpa_sim.c | 629 +++++++++++++++++
 drivers/virtio/virtio_vdpa.c            | 396 +++++++++++
 include/linux/vdpa.h                    | 253 +++++++
 include/linux/vhost_iotlb.h             |  47 ++
 include/linux/vringh.h                  |  36 +
 include/uapi/linux/vhost.h              |  24 +
 include/uapi/linux/vhost_types.h        |   8 +
 38 files changed, 4180 insertions(+), 248 deletions(-)
 delete mode 100644 drivers/vhost/Kconfig.vringh
 create mode 100644 drivers/vhost/iotlb.c
 create mode 100644 drivers/vhost/vdpa.c
 create mode 100644 drivers/virtio/vdpa/Kconfig
 create mode 100644 drivers/virtio/vdpa/Makefile
 create mode 100644 drivers/virtio/vdpa/ifcvf/Makefile
 create mode 100644 drivers/virtio/vdpa/ifcvf/ifcvf_base.c
 create mode 100644 drivers/virtio/vdpa/ifcvf/ifcvf_base.h
 create mode 100644 drivers/virtio/vdpa/ifcvf/ifcvf_main.c
 create mode 100644 drivers/virtio/vdpa/vdpa.c
 create mode 100644 drivers/virtio/vdpa/vdpa_sim/Makefile
 create mode 100644 drivers/virtio/vdpa/vdpa_sim/vdpa_sim.c
 create mode 100644 drivers/virtio/virtio_vdpa.c
 create mode 100644 include/linux/vdpa.h
 create mode 100644 include/linux/vhost_iotlb.h
```
#### [PATCH v3 kvmtool 00/32] Add reassignable BARs and PCIE 1.1 support
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
From patchwork Thu Mar 26 15:24:06 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 11460459
Return-Path: <SRS0=eSA5=5L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2DA5492A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Mar 2020 15:24:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id EEBC120774
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Mar 2020 15:24:55 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727714AbgCZPYz (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 26 Mar 2020 11:24:55 -0400
Received: from foss.arm.com ([217.140.110.172]:33664 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726034AbgCZPYy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 26 Mar 2020 11:24:54 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 2FF0D7FA;
        Thu, 26 Mar 2020 08:24:54 -0700 (PDT)
Received: from e123195-lin.cambridge.arm.com (e123195-lin.cambridge.arm.com
 [10.1.196.63])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 468AE3F71E;
        Thu, 26 Mar 2020 08:24:53 -0700 (PDT)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: kvm@vger.kernel.org
Cc: will@kernel.org, julien.thierry.kdev@gmail.com,
        andre.przywara@arm.com, sami.mujawar@arm.com,
        lorenzo.pieralisi@arm.com
Subject: [PATCH v3 kvmtool 00/32] Add reassignable BARs and PCIE 1.1 support
Date: Thu, 26 Mar 2020 15:24:06 +0000
Message-Id: <20200326152438.6218-1-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

kvmtool uses the Linux-only dt property 'linux,pci-probe-only' to prevent
it from trying to reassign the BARs. Let's make the BARs reassignable so we
can get rid of this band-aid.

Let's also extend the legacy PCI emulation, which came out in 1992, so we
can properly emulate the PCI Express version 1.1 protocol, which is new in
comparison, being published in 2005.

During device configuration, Linux can assign a region resource to a BAR
that temporarily overlaps with another device. This means that the code
that emulates BAR reassignment must be aware of all the registered PCI
devices. Because of this, and to avoid re-implementing the same code for
each emulated device, the algorithm for activating/deactivating emulation
as BAR addresses change lives completely inside the PCI code. Each device
registers two callback functions which are called when device emulation is
activated (for example, to activate emulation for a newly assigned BAR
address), respectively, when device emulation is deactivated (a previous
BAR address is changed, and emulation for that region must be deactivated).

There's one change this iteration that deserves a more elaborate
explanation. I have removed patch #9 "arm/pci: Fix PCI IO region". The
problem that the patch is trying to fix is still present: the PCI ioport
region overlaps with the 8250 uart, but the fix that the patch proposed was
incorrect, as it only works when the guest uses 4k pages (gory details at
[1]). I considered several fixes:

1. Changing the uart to live above the 64k address, which makes sense, as
on arm it is memory mapped anyway, and the Linux driver gets that address
from the dtb.

2. Changing the PCI CPU I/O addresses to live in the PCI MMIO space, and
keeping the PCI bus I/O addresses unchanged (in the 0-64K region).

3. Dropping PCI I/O ports altogether, which also makes sense: I/O ports are
an x86 architectural feature, and the PCI spec mandates that all controls
that are accessible via an I/O BAR should also be implemented by a memory
BAR.

However, all the above approaches are not the obviously right solution and
not trivial to implement for various reasons:

1. Software might rely on those addresses being fixed (kvm-unit-tests,
EDK2).

2. It requires invasive and subtle changes in the PCI and the device
emulation code, because now we have to distinguish between PCI CPU address
(which we trap and emulate) and PCI bus addresses, which will be used by
the guest to program the devices (for example, the I/O BAR addresses).

3. It requires changes to each device PCI code, because PCI I/O port
address requests failing will become a recoverable error on the arm and
arm64 architectures.

Considering the fact that this series is already very big, and this bug has
been present since 2014 without anyone complaining about it, I decided to
leave out any potential fixes. I will investigate which fix works better
and I will send it as a standalone series.

I tested the patches on an x86_64 and arm64 machine:

1. On AMD Seattle. Tried PCI passthrough using two different guests in each
case; one with 4k pages, and one with 64k pages (the CPU doesn't have
support for 16k pages):
- Intel 82574L Gigabit Ethernet card
- Samsung 970 Pro NVME (controller registers are in the same BAR region as the
  MSIX table and PBA, I wrote a nasty hack to make it work, will try to upstream
  something after this series)
- Realtek 8168 Gigabit Ethernet card
- NVIDIA Quadro P400 (nouveau probe fails because expansion ROM emulation not
  implemented in kvmtool, I will write a fix for that)
- AMD Firepro W2100 (amdgpu driver probe fails just like on the NVIDIA card)
- Seagate Barracuda 1000GB drive and Crucial MX500 SSD attached to a PCIE to
  SATA card.

I also wrote a kvm-unit-tests test that stresses the MMIO emulation locking
scheme that I implemented by spawning 4 vcpus (the Seattle machine has 8
physical CPUs) that toggle memory, and another 4 vcpus that read from the memory
region described by a BAR. I ran this under valgrind, and no deadlocks
use-after-free errors were detected.

2. Ryzen 3900x + Gigabyte x570 Aorus Master (bios F10). Tried PCI passthrough
with a Realtek 8168 and Intel 82574L Gigabit Ethernet cards at the same time,
plus running with --sdl enabled to test VESA device emulation at the same time.
I also managed to get the guest to do bar reassignment for one device by using
the kernel command line parameter pci.resource_alignment=16@pci:10ec:8168.

Patches 1-18 are fixes and cleanups, and can be merged independently. They
are pretty straightforward, so if the size of the series looks off-putting,
please review these first. I am aware that the series has grown quite a
lot, I am willing to split the fixes from the rest of the patches, or
whatever else can make reviewing easier.

Changes in v3:
* Patches 18, 24 and 26 are new.
* Dropped #9 "arm/pci: Fix PCI IO region" for reasons explained above.
* Reworded commit message for #12 "vfio/pci: Ignore expansion ROM BAR
  writes" to make it clear that kvmtool's implementation of VFIO doesn't
  support expansion BAR emulation.
* Moved variable declaration at the start of the function for #13
  "vfio/pci: Don't access unallocated regions".
* Patch #15 "Don't ignore errors registering a device, ioport or mmio
  emulation" uses ioport__remove consistenly.
* Reworked error cleanup for #16 "hw/vesa: Don't ignore fatal errors".
* Reworded commit message for #17 "hw/vesa: Set the size for BAR 0".
* Reworked #19 "ioport: mmio: Use a mutex and reference counting for
  locking" to also use reference counting to prevent races (and updated the
  commit message in the process).
* Added the function pci__bar_size to #20 "pci: Add helpers for BAR values
  and memory/IO space access".
* Protect mem_banks list with a mutex in #22 "vfio: Destroy memslot when
  unmapping the associated VAs"; also moved the munmap after the slot is
  destroyed, as per the KVM api.
* Dropped the rework of the vesa device in patch #27 "pci: Implement
  callbacks for toggling BAR emulation". Also added a few assert statements
  in some callbacks to make sure that they don't get called with an
  unxpected BAR number (which can only result from a coding error). Also
  return -ENOENT when kvm__deregister_mmio fails, to match ioport behavior
  and for better diagnostics.
* Dropped the PCI configuration write callback from the vesa device in #28
  "pci: Toggle BAR I/O and memory space emulation". Apparently, if we don't
  allow the guest kernel to disable BAR access, it treats the VESA device
  as a VGA boot device, instead of a regular VGA device, and Xorg cannot
  use it.
* Droped struct bar_info from #29 "pci: Implement reassignable BARs". Also
  changed pci_dev_err to pci_dev_warn in pci_{activate,deactivate}_bar,
  because the errors can be benign (they can happen because two vcpus race
  against each other to deactivate memory or I/O access, for example).
* Replaced the PCI device configuration space define with the actual
  number in #32 "arm/arm64: Add PCI Express 1.1 support". On some distros
  the defines weren't present in /usr/include/linux/pci_regs.h.
* Implemented other minor review comments.
* Gathered Reviewed-by tags.

Changes in v2:
* Patches 2, 11-18, 20, 22-27, 29 are new.
* Patches 11, 13, and 14 have been dropped.
* Reworked the way BAR reassignment is implemented.
* The patch "Add PCI Express 1.1 support" has been reworked to apply only
  to arm64. For x86 we would need ACPI support in order to advertise the
  location of the ECAM space.
* Gathered Reviewed-by tags.
* Implemented review comments.

[1] https://www.spinics.net/lists/kvm/msg209178.html
[2] https://www.spinics.net/lists/kvm/msg209178.html
[3] https://www.spinics.net/lists/arm-kernel/msg778623.html


Alexandru Elisei (27):
  Makefile: Use correct objcopy binary when cross-compiling for x86_64
  hw/i8042: Compile only for x86
  Remove pci-shmem device
  Check that a PCI device's memory size is power of two
  arm/pci: Advertise only PCI bus 0 in the DT
  vfio/pci: Allocate correct size for MSIX table and PBA BARs
  vfio/pci: Don't assume that only even numbered BARs are 64bit
  vfio/pci: Ignore expansion ROM BAR writes
  vfio/pci: Don't access unallocated regions
  virtio: Don't ignore initialization failures
  Don't ignore errors registering a device, ioport or mmio emulation
  hw/vesa: Don't ignore fatal errors
  hw/vesa: Set the size for BAR 0
  ioport: Fail when registering overlapping ports
  ioport: mmio: Use a mutex and reference counting for locking
  pci: Add helpers for BAR values and memory/IO space access
  virtio/pci: Get emulated region address from BARs
  vfio: Destroy memslot when unmapping the associated VAs
  vfio: Reserve ioports when configuring the BAR
  pci: Limit configuration transaction size to 32 bits
  vfio/pci: Don't write configuration value twice
  vesa: Create device exactly once
  pci: Implement callbacks for toggling BAR emulation
  pci: Toggle BAR I/O and memory space emulation
  pci: Implement reassignable BARs
  vfio: Trap MMIO access to BAR addresses which aren't page aligned
  arm/arm64: Add PCI Express 1.1 support

Julien Thierry (4):
  ioport: pci: Move port allocations to PCI devices
  pci: Fix ioport allocation size
  virtio/pci: Make memory and IO BARs independent
  arm/fdt: Remove 'linux,pci-probe-only' property

Sami Mujawar (1):
  pci: Fix BAR resource sizing arbitration

 Makefile                          |   6 +-
 arm/fdt.c                         |   1 -
 arm/include/arm-common/kvm-arch.h |   4 +-
 arm/ioport.c                      |   3 +-
 arm/pci.c                         |   4 +-
 builtin-run.c                     |   6 +-
 hw/i8042.c                        |  14 +-
 hw/pci-shmem.c                    | 400 ------------------------------
 hw/vesa.c                         | 113 ++++++---
 include/kvm/devices.h             |   3 +-
 include/kvm/ioport.h              |  12 +-
 include/kvm/kvm-config.h          |   2 +-
 include/kvm/kvm.h                 |  11 +-
 include/kvm/pci-shmem.h           |  32 ---
 include/kvm/pci.h                 | 163 +++++++++++-
 include/kvm/rbtree-interval.h     |   4 +-
 include/kvm/util.h                |   2 +
 include/kvm/vesa.h                |   6 +-
 include/kvm/virtio-pci.h          |   3 -
 include/kvm/virtio.h              |   7 +-
 include/linux/compiler.h          |   2 +-
 ioport.c                          | 108 ++++----
 kvm.c                             | 101 +++++++-
 mips/kvm.c                        |   3 +-
 mmio.c                            |  91 +++++--
 pci.c                             | 334 +++++++++++++++++++++++--
 powerpc/include/kvm/kvm-arch.h    |   2 +-
 powerpc/ioport.c                  |   3 +-
 powerpc/spapr_pci.c               |   2 +-
 vfio/core.c                       |  22 +-
 vfio/pci.c                        | 233 +++++++++++++----
 virtio/9p.c                       |   9 +-
 virtio/balloon.c                  |  10 +-
 virtio/blk.c                      |  14 +-
 virtio/console.c                  |  11 +-
 virtio/core.c                     |   9 +-
 virtio/mmio.c                     |  13 +-
 virtio/net.c                      |  32 +--
 virtio/pci.c                      | 206 ++++++++++-----
 virtio/scsi.c                     |  14 +-
 x86/include/kvm/kvm-arch.h        |   2 +-
 x86/ioport.c                      |  66 +++--
 42 files changed, 1287 insertions(+), 796 deletions(-)
 delete mode 100644 hw/pci-shmem.c
 delete mode 100644 include/kvm/pci-shmem.h
```
#### [PATCH v3 0/3] SELinux support for anonymous inodes and UFFD
##### From: Daniel Colascione <dancol@google.com>

```c
From patchwork Thu Mar 26 18:14:53 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Daniel Colascione <dancol@google.com>
X-Patchwork-Id: 11460773
Return-Path: <SRS0=eSA5=5L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DED7F1668
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Mar 2020 18:15:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id BEF9C2073E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Mar 2020 18:15:15 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="L4H51g1y"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727815AbgCZSPM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 26 Mar 2020 14:15:12 -0400
Received: from mail-qk1-f202.google.com ([209.85.222.202]:33235 "EHLO
        mail-qk1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727026AbgCZSPM (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 26 Mar 2020 14:15:12 -0400
Received: by mail-qk1-f202.google.com with SMTP id g25so5691447qka.0
        for <kvm@vger.kernel.org>; Thu, 26 Mar 2020 11:15:11 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=9W2imRwNIX90Y+pv7hvZUio45RVHKjTkCMpOp3XQz5g=;
        b=L4H51g1ye0QBy1pKesN7K+qpxcMZHaR/pvy4tsx/SOQ791OkKaMGWDK8acZTk9VIvo
         79JW3+veC4INQH6pDPz3HMLI5aMFnzztdMR7KcXsOg2upVPHvZ5+/9NY9d99M9AwsHxr
         0HywX1EfJOf+TjX+zojuN3zm1Rq0DcTyRlJCyG9OMVaQwX1VwLwOH89FeCWjtk0CaNY9
         DxCYvgfbdWT2LSpz7hnG+2EE6W3BuqfCdVvxI2Qj0jh6oObj8Zd456/UGglmhP8oo3pF
         IpTY/tcb2l+BkqjcDQeaamxI4lbEhzTiRJJtuLRYW4vTY8iTvatwecihnymCxzMYIDbS
         hvfw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=9W2imRwNIX90Y+pv7hvZUio45RVHKjTkCMpOp3XQz5g=;
        b=jXKvp3fJ4WQ2qu1k8mlWG11cNFHD3/j7nevOhpkxkBptiyINIoqYcA0xX7ZdekJbQJ
         iXVZBmm1vQ43Mw/zZY+TkM3Epon4nruiizWzdhmer97cELKjSVvzI67uiXxt2PWMVaOr
         YPOzBcQDP47ZRfepXjYDsEGpuMRgtren4zZz/c1YW/4O+zk2ZY3DumkbnE43f2ev++EV
         m76E2fpU1AnNun9eR9cZIwnuPBrYWsroaeY6kkLhNZmPsfXDbElwG8zxZdNJ35pTv2F9
         zIllrSr3cqTtG0yzdj7j5J8kc6LnecHEfxSX1I6A6D3GCpT6odRnPVC0OfTvLrxsI9Ja
         xEwg==
X-Gm-Message-State: ANhLgQ0uD/t+tZP+gEZuzPiII7w3rzVAwBoZZRjtj/roTkIknGvHHoKc
        ydWhgMXmQr1CRQBfOxJOJJrBrwEQamc=
X-Google-Smtp-Source: 
 ADFU+vuXYWs53KZQSCzq/xUwtE1DCsUixB0nXsvXZzDLn/OQfnLie5fjL6+pvJ2MBJlcFVtiiQax9ZZZqwI=
X-Received: by 2002:aed:37c3:: with SMTP id j61mr639522qtb.284.1585246510936;
 Thu, 26 Mar 2020 11:15:10 -0700 (PDT)
Date: Thu, 26 Mar 2020 11:14:53 -0700
In-Reply-To: <20200214032635.75434-1-dancol@google.com>
Message-Id: <20200326181456.132742-1-dancol@google.com>
Mime-Version: 1.0
References: <20200214032635.75434-1-dancol@google.com>
X-Mailer: git-send-email 2.25.1.696.g5e7596f4ac-goog
Subject: [PATCH v3 0/3] SELinux support for anonymous inodes and UFFD
From: Daniel Colascione <dancol@google.com>
To: timmurray@google.com, selinux@vger.kernel.org,
        linux-security-module@vger.kernel.org,
        linux-fsdevel@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, viro@zeniv.linux.org.uk, paul@paul-moore.com,
        nnk@google.com, sds@tycho.nsa.gov, lokeshgidra@google.com,
        jmorris@namei.org
Cc: Daniel Colascione <dancol@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Userfaultfd in unprivileged contexts could be potentially very
useful. We'd like to harden userfaultfd to make such unprivileged use
less risky. This patch series allows SELinux to manage userfaultfd
file descriptors and in the future, other kinds of
anonymous-inode-based file descriptor.  SELinux policy authors can
apply policy types to anonymous inodes by providing name-based
transition rules keyed off the anonymous inode internal name (
"[userfaultfd]" in the case of userfaultfd(2) file descriptors) and
applying policy to the new SIDs thus produced.

Inside the kernel, a pair of new anon_inodes interface,
anon_inode_getfile_secure and anon_inode_getfd_secure, allow callers
to opt into this SELinux management. In this new "secure" mode,
anon_inodes creates new ephemeral inodes for anonymous file objects
instead of reusing the normal anon_inodes singleton dummy inode. A new
LSM hook gives security modules an opportunity to configure and veto
these ephemeral inodes.

This patch series is one of two fork of [1] and is an
alternative to [2].

The primary difference between the two patch series is that this
partch series creates a unique inode for each "secure" anonymous
inode, while the other patch series ([2]) continues using the
singleton dummy anonymous inode and adds a way to attach SELinux
security information directly to file objects.

I prefer the approach in this patch series because 1) it's a smaller
patch than [2], and 2) it produces a more regular security
architecture: in this patch series, secure anonymous inodes aren't
S_PRIVATE and they maintain the SELinux property that the label for a
file is in its inode. We do need an additional inode per anonymous
file, but per-struct-file inode creation doesn't seem to be a problem
for pipes and sockets.

The previous version of this feature ([1]) created a new SELinux
security class for userfaultfd file descriptors. This version adopts
the generic transition-based approach of [2].

This patch series also differs from [2] in that it doesn't affect all
anonymous inodes right away --- instead requiring anon_inodes callers
to opt in --- but this difference isn't one of basic approach. The
important question to resolve is whether we should be creating new
inodes or enhancing per-file data.

Changes from the first version of the patch:

  - Removed some error checks
  - Defined a new anon_inode SELinux class to resolve the
    ambiguity in [3]
  - Inherit sclass as well as descriptor from context inode

Changes from the second version of the patch:

  - Fixed example policy in the commit message to reflect the use of
    the new anon_inode class.

[1] https://lore.kernel.org/lkml/20200211225547.235083-1-dancol@google.com/
[2] https://lore.kernel.org/linux-fsdevel/20200213194157.5877-1-sds@tycho.nsa.gov/
[3] https://lore.kernel.org/lkml/23f725ca-5b5a-5938-fcc8-5bbbfc9ba9bc@tycho.nsa.gov/

Daniel Colascione (3):
  Add a new LSM-supporting anonymous inode interface
  Teach SELinux about anonymous inodes
  Wire UFFD up to SELinux

 fs/anon_inodes.c                    | 196 ++++++++++++++++++++++------
 fs/userfaultfd.c                    |  30 ++++-
 include/linux/anon_inodes.h         |  13 ++
 include/linux/lsm_hooks.h           |   9 ++
 include/linux/security.h            |   4 +
 security/security.c                 |  10 ++
 security/selinux/hooks.c            |  54 ++++++++
 security/selinux/include/classmap.h |   2 +
 8 files changed, 272 insertions(+), 46 deletions(-)
```
#### [PATCH v4 0/3] SELinux support for anonymous inodes and UFFD
##### From: Daniel Colascione <dancol@google.com>

```c
From patchwork Thu Mar 26 20:06:31 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Daniel Colascione <dancol@google.com>
X-Patchwork-Id: 11460979
Return-Path: <SRS0=eSA5=5L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 64AD61668
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Mar 2020 20:06:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 45BBC206E6
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 26 Mar 2020 20:06:46 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="oQg2HiJA"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728641AbgCZUGp (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 26 Mar 2020 16:06:45 -0400
Received: from mail-pf1-f202.google.com ([209.85.210.202]:46114 "EHLO
        mail-pf1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727984AbgCZUGp (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 26 Mar 2020 16:06:45 -0400
Received: by mail-pf1-f202.google.com with SMTP id f75so6163002pfa.13
        for <kvm@vger.kernel.org>; Thu, 26 Mar 2020 13:06:44 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=WqHax6ECl9wbInrMxjIjOM9cZAwTrPkoL2M2jFKPBQE=;
        b=oQg2HiJAJN0uq3CanDGzoJhuUjBYjvhnGM82wp7T8u1ZLdJc0emxPSWGDOVo2hwXyD
         oYhF+R4VmJyHhW9agDvAQwLEQehvPDqs2xMeloGW6iyyNl7BkF+BMNrw6sO8n5tEHSRW
         Bj9P4BPDq3/5vV7bdFky1PCeCR2OwIF62INk4/iglpEogfPbio/6/tuFzLNw2BTLZnIM
         szYZf1bycO6HgHYsEnY0Fz1gYItaYnVEORPALjWBYguN7JqK9Z7cKiRowmRewMd8xCuQ
         6QR0/l8leAZRocfTh5jgbffUm6anAdrZ0D82jPJYwvqKEtPgt/HsDIA4PDCLHV2pVl9e
         5qwA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=WqHax6ECl9wbInrMxjIjOM9cZAwTrPkoL2M2jFKPBQE=;
        b=GExU6TZJM8MsJXtJ6RPGARqg8xK0FdB3zR1Tpfny+nLsYy4SkbAu/BFW6YXMC7is6F
         fidZCNiLHPa75Zx6mPvHJV2tsAALDPbVJVQCFv0g5z18A/7Tv/GbY3rewDvT5eCxtYd/
         5I0W8hcmVleRsHS3UOLK79V3hZQcFPv4M2FqI4qKOiaFiPojBks4ZYtMAW0eT7YXlK1q
         w0tVoT/9GjGCPAnZmbxndn760Wtz7rlyIHUy3GlzWnCB0W7zaVcnhEqjtx/z/TUYlhcs
         x31PzuPmxdrPVzN2zcIbL5vdxsnR3mO404aJs5Qu1G/GSbIIsOudN6TgxO9Ni/jZ5xPu
         uv+Q==
X-Gm-Message-State: ANhLgQ0dH8KN2zEEHPv/uvhCk9FYc40fynJO4CKrY5qSjHPQChdsqEgl
        ox2oxlFJOUx7pN5eQiCy2uKVd3qwnEk=
X-Google-Smtp-Source: 
 ADFU+vvsk68FMQSxurQFf3aAeMUtjRxGtYQGqNwjBsk1ShThaxSUYG2MrLAemrcldb5fjvyCliNa2Z6slbk=
X-Received: by 2002:a17:90a:e289:: with SMTP id
 d9mr1801523pjz.172.1585253203623;
 Thu, 26 Mar 2020 13:06:43 -0700 (PDT)
Date: Thu, 26 Mar 2020 13:06:31 -0700
In-Reply-To: <20200326181456.132742-1-dancol@google.com>
Message-Id: <20200326200634.222009-1-dancol@google.com>
Mime-Version: 1.0
References: <20200326181456.132742-1-dancol@google.com>
X-Mailer: git-send-email 2.25.1.696.g5e7596f4ac-goog
Subject: [PATCH v4 0/3] SELinux support for anonymous inodes and UFFD
From: Daniel Colascione <dancol@google.com>
To: timmurray@google.com, selinux@vger.kernel.org,
        linux-security-module@vger.kernel.org,
        linux-fsdevel@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, viro@zeniv.linux.org.uk, paul@paul-moore.com,
        nnk@google.com, sds@tycho.nsa.gov, lokeshgidra@google.com,
        jmorris@namei.org
Cc: Daniel Colascione <dancol@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Userfaultfd in unprivileged contexts could be potentially very
useful. We'd like to harden userfaultfd to make such unprivileged use
less risky. This patch series allows SELinux to manage userfaultfd
file descriptors and in the future, other kinds of
anonymous-inode-based file descriptor.  SELinux policy authors can
apply policy types to anonymous inodes by providing name-based
transition rules keyed off the anonymous inode internal name (
"[userfaultfd]" in the case of userfaultfd(2) file descriptors) and
applying policy to the new SIDs thus produced.

Inside the kernel, a pair of new anon_inodes interface,
anon_inode_getfile_secure and anon_inode_getfd_secure, allow callers
to opt into this SELinux management. In this new "secure" mode,
anon_inodes creates new ephemeral inodes for anonymous file objects
instead of reusing the normal anon_inodes singleton dummy inode. A new
LSM hook gives security modules an opportunity to configure and veto
these ephemeral inodes.

This patch series is one of two fork of [1] and is an
alternative to [2].

The primary difference between the two patch series is that this
partch series creates a unique inode for each "secure" anonymous
inode, while the other patch series ([2]) continues using the
singleton dummy anonymous inode and adds a way to attach SELinux
security information directly to file objects.

I prefer the approach in this patch series because 1) it's a smaller
patch than [2], and 2) it produces a more regular security
architecture: in this patch series, secure anonymous inodes aren't
S_PRIVATE and they maintain the SELinux property that the label for a
file is in its inode. We do need an additional inode per anonymous
file, but per-struct-file inode creation doesn't seem to be a problem
for pipes and sockets.

The previous version of this feature ([1]) created a new SELinux
security class for userfaultfd file descriptors. This version adopts
the generic transition-based approach of [2].

This patch series also differs from [2] in that it doesn't affect all
anonymous inodes right away --- instead requiring anon_inodes callers
to opt in --- but this difference isn't one of basic approach. The
important question to resolve is whether we should be creating new
inodes or enhancing per-file data.

Changes from the first version of the patch:

  - Removed some error checks
  - Defined a new anon_inode SELinux class to resolve the
    ambiguity in [3]
  - Inherit sclass as well as descriptor from context inode

Changes from the second version of the patch:

  - Fixed example policy in the commit message to reflect the use of
    the new anon_inode class.

Changes from the third version of the patch:

  - Dropped the fops parameter to the LSM hook
  - Documented hook parameters
  - Fixed incorrect class used for SELinux transition
  - Removed stray UFFD changed early in the series
  - Removed a redundant ERR_PTR(PTR_ERR())

[1] https://lore.kernel.org/lkml/20200211225547.235083-1-dancol@google.com/
[2] https://lore.kernel.org/linux-fsdevel/20200213194157.5877-1-sds@tycho.nsa.gov/
[3] https://lore.kernel.org/lkml/23f725ca-5b5a-5938-fcc8-5bbbfc9ba9bc@tycho.nsa.gov/

Daniel Colascione (3):
  Add a new LSM-supporting anonymous inode interface
  Teach SELinux about anonymous inodes
  Wire UFFD up to SELinux

 fs/anon_inodes.c                    | 196 ++++++++++++++++++++++------
 fs/userfaultfd.c                    |  30 ++++-
 include/linux/anon_inodes.h         |  13 ++
 include/linux/lsm_hooks.h           |  11 ++
 include/linux/security.h            |   3 +
 security/security.c                 |   9 ++
 security/selinux/hooks.c            |  53 ++++++++
 security/selinux/include/classmap.h |   2 +
 8 files changed, 271 insertions(+), 46 deletions(-)
```
