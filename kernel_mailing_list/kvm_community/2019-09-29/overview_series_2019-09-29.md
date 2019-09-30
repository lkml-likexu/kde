#### [PATCH] KVM: VMX: Remove proprietary handling of unexpected exit-reasons
##### From: Liran Alon <liran.alon@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liran Alon <liran.alon@oracle.com>
X-Patchwork-Id: 11165661
Return-Path: <SRS0=JqV3=XY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 695991599
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 29 Sep 2019 14:51:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3A8912082F
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 29 Sep 2019 14:51:27 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="dW0RJUVx"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726827AbfI2OvP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 29 Sep 2019 10:51:15 -0400
Received: from userp2120.oracle.com ([156.151.31.85]:56222 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726018AbfI2OvP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 29 Sep 2019 10:51:15 -0400
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x8TEdJNM101979;
        Sun, 29 Sep 2019 14:50:38 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : mime-version : content-transfer-encoding;
 s=corp-2019-08-05; bh=Fhg9wY0MN9NjJv1FypLcGMLYNfuFMXgxdxO/SBR7uKs=;
 b=dW0RJUVxZNqOKLVB4m+Vx0vKKB5xleGC1eSrsIzRYXflPuU8co3aQAYjsgAwIaPykxLw
 MHisdHofIvqwOw/K6ZeTCB/OOJlyy/jC56abWODA450ADBuO68g1Djg3Qjgk1EF64K8P
 hyvZbbDc1CUd3ShlTjJ4QEiOBc/VIM/fc32sb0hpoxBIbvMwKDnNFvLQT0D4TCpWBW52
 W/SunpLvEY9HjDem40ZIoKBWE6dItKTGonJ/AWp3W1ybNIIzad22vgS2Q9YfuMAfeieF
 xMh8cSBBN8GdHJUCSltImYbADvZDKsv6y3Mqd9EsWouvFZy4Ked/CjoV0Zpaz2Qt+9Rl iA==
Received: from aserp3030.oracle.com (aserp3030.oracle.com [141.146.126.71])
        by userp2120.oracle.com with ESMTP id 2va05raxmh-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Sun, 29 Sep 2019 14:50:38 +0000
Received: from pps.filterd (aserp3030.oracle.com [127.0.0.1])
        by aserp3030.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x8TEca9g074264;
        Sun, 29 Sep 2019 14:50:37 GMT
Received: from aserv0121.oracle.com (aserv0121.oracle.com [141.146.126.235])
        by aserp3030.oracle.com with ESMTP id 2vahp9k2kp-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Sun, 29 Sep 2019 14:50:37 +0000
Received: from abhmp0013.oracle.com (abhmp0013.oracle.com [141.146.116.19])
        by aserv0121.oracle.com (8.14.4/8.13.8) with ESMTP id x8TEob4j023636;
        Sun, 29 Sep 2019 14:50:37 GMT
Received: from spark.ravello.local (/213.57.127.2)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Sun, 29 Sep 2019 07:50:36 -0700
From: Liran Alon <liran.alon@oracle.com>
To: pbonzini@redhat.com, rkrcmar@redhat.com, kvm@vger.kernel.org
Cc: tao3.xu@intel.com, sean.j.christopherson@intel.com,
        jmattson@google.com, vkuznets@redhat.com,
        Liran Alon <liran.alon@oracle.com>
Subject: [PATCH] KVM: VMX: Remove proprietary handling of unexpected
 exit-reasons
Date: Sun, 29 Sep 2019 17:50:18 +0300
Message-Id: <20190929145018.120753-1-liran.alon@oracle.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9394
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=0
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=999
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1908290000 definitions=main-1909290166
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9394
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=0 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=999 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1908290000
 definitions=main-1909290166
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit bf653b78f960 ("KVM: vmx: Introduce handle_unexpected_vmexit
and handle WAITPKG vmexit") introduced proprietary handling of
specific exit-reasons that should not be raised by CPU because
KVM configures VMCS such that they should never be raised.

However, since commit 7396d337cfad ("KVM: x86: Return to userspace
with internal error on unexpected exit reason"), VMX & SVM
exit handlers were modified to generically handle all unexpected
exit-reasons by returning to userspace with internal error.

Therefore, there is no need for proprietary handling of specific
unexpected exit-reasons (This proprietary handling also introduced
inconsistency for these exit-reasons to silently skip guest instruction
instead of return to userspace on internal-error).

Fixes: bf653b78f960 ("KVM: vmx: Introduce handle_unexpected_vmexit and handle WAITPKG vmexit")

Signed-off-by: Liran Alon <liran.alon@oracle.com>
---
 arch/x86/kvm/vmx/vmx.c | 12 ------------
 1 file changed, 12 deletions(-)

```
#### [PATCH v2] KVM: Don't shrink/grow vCPU halt_poll_ns if host side polling is disabled
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11165581
Return-Path: <SRS0=JqV3=XY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 859B216C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 29 Sep 2019 01:07:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5A20B21655
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 29 Sep 2019 01:07:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="Rs7Te/s2"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728779AbfI2BHD (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 28 Sep 2019 21:07:03 -0400
Received: from mail-pl1-f194.google.com ([209.85.214.194]:37160 "EHLO
        mail-pl1-f194.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728666AbfI2BHD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 28 Sep 2019 21:07:03 -0400
Received: by mail-pl1-f194.google.com with SMTP id u20so2488283plq.4;
        Sat, 28 Sep 2019 18:07:02 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=lEm23RZXulSmlP370lFYOGBjjNx5eqJhq1MeUNEd3jQ=;
        b=Rs7Te/s2njqQvR8Z/hq50Gss4qS2rGACcqiS/FdSM0ssXWVXRiVprx2rdNU93oHHwb
         37FD6/AvGJLRqZVDXgrDBX/uMwM9ZHTO3qRKtEJlDAAhMEkDZ1kbb7m8Gu20aff9smXZ
         MnLE4zJZjUosvJ7k5xfBBREGr6+gN+oLkGJULlMOpJvXfRLVARb7ez4a2rM6EbFxC2ZO
         t6vpY4zWEO20utF9QJmv3nv7VAkAg6xnnuwyfs7R4M4GK4j11dHLlYMTzRbysL1x2sib
         7KQkdjbEKHfGbGHOTLqLF5bUUsXytLlx2Mhu4/P/bO8JHoBFTCljDF/Sz0dtx1xBLLO2
         oFrQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=lEm23RZXulSmlP370lFYOGBjjNx5eqJhq1MeUNEd3jQ=;
        b=cuKVvJB2ENZXf+UnT9R2ahTUBMjQYlh8+DfPltjOjjZB/tPaUdomEyrpka9zNMlmww
         aRhHLq3UUSAGXOqTsp5TzUQM1IImNerIHoPHQ8+iMhMLqCRWruLYE7OKXAyyUFjnjf+n
         U0RBsneSmgwaP1P6nMGj8iKfqw2wFMnnW8REcrLYvi+zMY0Vf5CYxO7l87wQFtwZ4+K8
         E+ddYBxPq+3GU5XphVo1O+aHbaPYduRC2jhZMaT8rNUvtb1HjnDK/4bSsmS5pMrPNND7
         o/5Op56sDSGfEpKxK/qMsXA2A72FbAjEnq6Nefu3UY+CXLtBtSpGCu2CZ15po1K//So8
         ic4A==
X-Gm-Message-State: APjAAAWMKKotVPetRfmLyZ4JZDpCn5zh8LtWaU7slorB21yDQZpCvzVl
        YyUbvvouh5nyvQnGS4hFgbAgolAw
X-Google-Smtp-Source: 
 APXvYqwbadV9s3qfd7nhJQvCRIhGv/fSpBO72pITQ3mh60EycuNRVNiH688w3agRcg+hRlJBm4Yddw==
X-Received: by 2002:a17:902:d685:: with SMTP id
 v5mr12683022ply.15.1569719222264;
        Sat, 28 Sep 2019 18:07:02 -0700 (PDT)
Received: from localhost.localdomain ([203.205.141.123])
        by smtp.googlemail.com with ESMTPSA id
 b69sm7336170pfb.132.2019.09.28.18.06.59
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-SHA bits=128/128);
        Sat, 28 Sep 2019 18:07:01 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Wanpeng Li <wanpengli@tencent.com>,
 Jim Mattson <jmattson@google.com>, Joerg Roedel <joro@8bytes.org>,
 Marcelo Tosatti <mtosatti@redhat.com>
Subject: [PATCH v2] KVM: Don't shrink/grow vCPU halt_poll_ns if host side
 polling is disabled
Date: Sun, 29 Sep 2019 09:06:56 +0800
Message-Id: <1569719216-32080-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

Don't waste cycles to shrink/grow vCPU halt_poll_ns if host 
side polling is disabled.

Acked-by: Marcelo Tosatti <mtosatti@redhat.com>
Cc: Marcelo Tosatti <mtosatti@redhat.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
v1 -> v2: 
 * fix coding style

 virt/kvm/kvm_main.c | 29 ++++++++++++++++-------------
 1 file changed, 16 insertions(+), 13 deletions(-)

```
#### [PATCH v5 1/2] x86/cpu: Add support for UMONITOR/UMWAIT/TPAUSE
##### From: Tao Xu <tao3.xu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Tao Xu <tao3.xu@intel.com>
X-Patchwork-Id: 11165597
Return-Path: <SRS0=JqV3=XY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E48451747
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 29 Sep 2019 02:02:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CD1BE214D8
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 29 Sep 2019 02:02:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728831AbfI2B5X (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 28 Sep 2019 21:57:23 -0400
Received: from mga03.intel.com ([134.134.136.65]:14348 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728569AbfI2B5X (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 28 Sep 2019 21:57:23 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga103.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 28 Sep 2019 18:57:23 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,561,1559545200";
   d="scan'208";a="204501452"
Received: from tao-optiplex-7060.sh.intel.com ([10.239.159.36])
  by fmsmga001.fm.intel.com with ESMTP; 28 Sep 2019 18:57:21 -0700
From: Tao Xu <tao3.xu@intel.com>
To: pbonzini@redhat.com, rth@twiddle.net, ehabkost@redhat.com,
        mtosatti@redhat.com
Cc: qemu-devel@nongnu.org, kvm@vger.kernel.org, tao3.xu@intel.com,
        jingqi.liu@intel.com
Subject: [PATCH v5 1/2] x86/cpu: Add support for UMONITOR/UMWAIT/TPAUSE
Date: Sun, 29 Sep 2019 09:57:17 +0800
Message-Id: <20190929015718.19562-2-tao3.xu@intel.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20190929015718.19562-1-tao3.xu@intel.com>
References: <20190929015718.19562-1-tao3.xu@intel.com>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

UMONITOR, UMWAIT and TPAUSE are a set of user wait instructions.
This patch adds support for user wait instructions in KVM. Availability
of the user wait instructions is indicated by the presence of the CPUID
feature flag WAITPKG CPUID.0x07.0x0:ECX[5]. User wait instructions may
be executed at any privilege level, and use IA32_UMWAIT_CONTROL MSR to
set the maximum time.

The patch enable the umonitor, umwait and tpause features in KVM.
Because umwait and tpause can put a (psysical) CPU into a power saving
state, by default we dont't expose it to kvm and enable it only when
guest CPUID has it. And use QEMU command-line "-overcommit cpu-pm=on"
(enable_cpu_pm is enabled), a VM can use UMONITOR, UMWAIT and TPAUSE
instructions. If the instruction causes a delay, the amount of time
delayed is called here the physical delay. The physical delay is first
computed by determining the virtual delay (the time to delay relative to
the VM’s timestamp counter). Otherwise, UMONITOR, UMWAIT and TPAUSE cause
an invalid-opcode exception(#UD).

The release document ref below link:
https://software.intel.com/sites/default/files/\
managed/39/c5/325462-sdm-vol-1-2abcd-3abcd.pdf

Co-developed-by: Jingqi Liu <jingqi.liu@intel.com>
Signed-off-by: Jingqi Liu <jingqi.liu@intel.com>
Signed-off-by: Tao Xu <tao3.xu@intel.com>
---

Changes in v5:
    - Remove CPUID_7_0_ECX_WAITPKG if enable_cpu_pm is not set.
    (Paolo)
---
 target/i386/cpu.c | 3 ++-
 target/i386/cpu.h | 1 +
 target/i386/kvm.c | 6 ++++++
 3 files changed, 9 insertions(+), 1 deletion(-)

```
