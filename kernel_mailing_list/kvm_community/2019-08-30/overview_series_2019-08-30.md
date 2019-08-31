#### [PATCH v4 01/10] KVM: arm64: Document PV-time interface
##### From: Steven Price <steven.price@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Steven Price <Steven.Price@arm.com>
X-Patchwork-Id: 11123481
Return-Path: <SRS0=4maQ=W2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 91A0D112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 30 Aug 2019 08:44:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6F42E238CF
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 30 Aug 2019 08:44:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727992AbfH3InJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 30 Aug 2019 04:43:09 -0400
Received: from foss.arm.com ([217.140.110.172]:56154 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726200AbfH3InH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 30 Aug 2019 04:43:07 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id D0577360;
        Fri, 30 Aug 2019 01:43:06 -0700 (PDT)
Received: from e112269-lin.arm.com (e112269-lin.cambridge.arm.com
 [10.1.196.133])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 ABA2F3F718;
        Fri, 30 Aug 2019 01:43:04 -0700 (PDT)
From: Steven Price <steven.price@arm.com>
To: Marc Zyngier <maz@kernel.org>, Will Deacon <will@kernel.org>,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu
Cc: Steven Price <steven.price@arm.com>,
 Catalin Marinas <catalin.marinas@arm.com>,
 Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Russell King <linux@armlinux.org.uk>, James Morse <james.morse@arm.com>,
 Julien Thierry <julien.thierry.kdev@gmail.com>,
 Suzuki K Pouloze <suzuki.poulose@arm.com>,
 Mark Rutland <mark.rutland@arm.com>, kvm@vger.kernel.org,
 linux-doc@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH v4 01/10] KVM: arm64: Document PV-time interface
Date: Fri, 30 Aug 2019 09:42:46 +0100
Message-Id: <20190830084255.55113-2-steven.price@arm.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20190830084255.55113-1-steven.price@arm.com>
References: <20190830084255.55113-1-steven.price@arm.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Introduce a paravirtualization interface for KVM/arm64 based on the
"Arm Paravirtualized Time for Arm-Base Systems" specification DEN 0057A.

This only adds the details about "Stolen Time" as the details of "Live
Physical Time" have not been fully agreed.

User space can specify a reserved area of memory for the guest and
inform KVM to populate the memory with information on time that the host
kernel has stolen from the guest.

A hypercall interface is provided for the guest to interrogate the
hypervisor's support for this interface and the location of the shared
memory structures.

Signed-off-by: Steven Price <steven.price@arm.com>
---
 Documentation/virt/kvm/arm/pvtime.txt   | 64 +++++++++++++++++++++++++
 Documentation/virt/kvm/devices/vcpu.txt | 14 ++++++
 2 files changed, 78 insertions(+)
 create mode 100644 Documentation/virt/kvm/arm/pvtime.txt

diff --git a/Documentation/virt/kvm/arm/pvtime.txt b/Documentation/virt/kvm/arm/pvtime.txt
new file mode 100644
index 000000000000..dda3f0f855b9
--- /dev/null
+++ b/Documentation/virt/kvm/arm/pvtime.txt
@@ -0,0 +1,64 @@
+Paravirtualized time support for arm64
+======================================
+
+Arm specification DEN0057/A defined a standard for paravirtualised time
+support for AArch64 guests:
+
+https://developer.arm.com/docs/den0057/a
+
+KVM/arm64 implements the stolen time part of this specification by providing
+some hypervisor service calls to support a paravirtualized guest obtaining a
+view of the amount of time stolen from its execution.
+
+Two new SMCCC compatible hypercalls are defined:
+
+PV_FEATURES 0xC5000020
+PV_TIME_ST  0xC5000022
+
+These are only available in the SMC64/HVC64 calling convention as
+paravirtualized time is not available to 32 bit Arm guests. The existence of
+the PV_FEATURES hypercall should be probed using the SMCCC 1.1 ARCH_FEATURES
+mechanism before calling it.
+
+PV_FEATURES
+    Function ID:  (uint32)  : 0xC5000020
+    PV_func_id:   (uint32)  : Either PV_TIME_LPT or PV_TIME_ST
+    Return value: (int32)   : NOT_SUPPORTED (-1) or SUCCESS (0) if the relevant
+                              PV-time feature is supported by the hypervisor.
+
+PV_TIME_ST
+    Function ID:  (uint32)  : 0xC5000022
+    Return value: (int64)   : IPA of the stolen time data structure for this
+                              VCPU. On failure:
+                              NOT_SUPPORTED (-1)
+
+The IPA returned by PV_TIME_ST should be mapped by the guest as normal memory
+with inner and outer write back caching attributes, in the inner shareable
+domain. A total of 16 bytes from the IPA returned are guaranteed to be
+meaningfully filled by the hypervisor (see structure below).
+
+PV_TIME_ST returns the structure for the calling VCPU.
+
+Stolen Time
+-----------
+
+The structure pointed to by the PV_TIME_ST hypercall is as follows:
+
+  Field       | Byte Length | Byte Offset | Description
+  ----------- | ----------- | ----------- | --------------------------
+  Revision    |      4      |      0      | Must be 0 for version 0.1
+  Attributes  |      4      |      4      | Must be 0
+  Stolen time |      8      |      8      | Stolen time in unsigned
+              |             |             | nanoseconds indicating how
+              |             |             | much time this VCPU thread
+              |             |             | was involuntarily not
+              |             |             | running on a physical CPU.
+
+The structure will be updated by the hypervisor prior to scheduling a VCPU. It
+will be present within a reserved region of the normal memory given to the
+guest. The guest should not attempt to write into this memory. There is a
+structure per VCPU of the guest.
+
+For the user space interface see Documentation/virt/kvm/devices/vcpu.txt
+section "3. GROUP: KVM_ARM_VCPU_PVTIME_CTRL".
+
```
#### [PATCH v3 1/4] KVM: selftests: Move vm type into _vm_create() internally
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11122799
Return-Path: <SRS0=4maQ=W2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 69D351399
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 30 Aug 2019 01:36:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 459E222CF5
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 30 Aug 2019 01:36:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727675AbfH3Bgi (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 29 Aug 2019 21:36:38 -0400
Received: from mx1.redhat.com ([209.132.183.28]:50788 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727213AbfH3Bgh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Aug 2019 21:36:37 -0400
Received: from mail-pl1-f199.google.com (mail-pl1-f199.google.com
 [209.85.214.199])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id DE01D2A09D8
        for <kvm@vger.kernel.org>; Fri, 30 Aug 2019 01:36:36 +0000 (UTC)
Received: by mail-pl1-f199.google.com with SMTP id t2so3102980plq.11
        for <kvm@vger.kernel.org>; Thu, 29 Aug 2019 18:36:36 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=OKXdosyqABi9C2gUBPMdwJsytKQYxgvWS0ODiVfOX34=;
        b=Z0r9rS2BNoxYY/KQY/G1aZ1CI70pOvNmIn+6PVFRDwS3GBRp3DrRECdTWs12bHBPzh
         kNDcgTqWidH2NrYK1wx921hpYgJqbYzpHu5NtbxPYSORvHzAyrIMf/9QhcwUcorcoKWi
         22eZq+Q5qVPjaz1i9y503eaeU4dqBRecLW+bVoYEtMUR0O3qJkBSr5peVVDYv+GE27R+
         AuGprDibSXMiGniBGc5OdK29q9lIq/Rl6DhBc7ee65qHkMfsV+9BeFWKfWzA7OHeY6Dy
         OlgecBu1mVPmqHd4EhIyaEWuhab8nveHmQ63QmO5jK8jo0ElDSSRtIwhGfPkKzHXEA7k
         iVjA==
X-Gm-Message-State: APjAAAVlD6gMoVXo5mlbhQnm90nN14DG9FU1837Ac1MNf0+4xwsoK8qx
        9hJ8S6J68Om+0rXXKPyR6GPLgojmw1brtsbjXG9hM/8tT4wOc/0w6Oles9GX+2hCoAB6ogRTo8k
        wngL5gdb9y0sW
X-Received: by 2002:a17:902:bd0b:: with SMTP id
 p11mr6892600pls.46.1567128996389;
        Thu, 29 Aug 2019 18:36:36 -0700 (PDT)
X-Google-Smtp-Source: 
 APXvYqyvKrzcXJdENL8MNxQqyEtgoGbu1tY0m/pNl+n78glEILSI7LJ8m8DvTz1e/5Z6rrYimREzuQ==
X-Received: by 2002:a17:902:bd0b:: with SMTP id
 p11mr6892590pls.46.1567128996150;
        Thu, 29 Aug 2019 18:36:36 -0700 (PDT)
Received: from xz-x1.redhat.com ([209.132.188.80])
        by smtp.gmail.com with ESMTPSA id
 l3sm3426323pjq.24.2019.08.29.18.36.32
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 29 Aug 2019 18:36:35 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Thomas Huth <thuth@redhat.com>, Andrew Jones <drjones@redhat.com>,
 peterx@redhat.com
Subject: [PATCH v3 1/4] KVM: selftests: Move vm type into _vm_create()
 internally
Date: Fri, 30 Aug 2019 09:36:16 +0800
Message-Id: <20190830013619.18867-2-peterx@redhat.com>
X-Mailer: git-send-email 2.21.0
In-Reply-To: <20190830013619.18867-1-peterx@redhat.com>
References: <20190830013619.18867-1-peterx@redhat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Rather than passing the vm type from the top level to the end of vm
creation, let's simply keep that as an internal of kvm_vm struct and
decide the type in _vm_create().  Several reasons for doing this:

- The vm type is only decided by physical address width and currently
  only used in aarch64, so we've got enough information as long as
  we're passing vm_guest_mode into _vm_create(),

- This removes a loop dependency between the vm->type and creation of
  vms.  That's why now we need to parse vm_guest_mode twice sometimes,
  once in run_test() and then again in _vm_create().  The follow up
  patches will move on to clean up that as well so we can have a
  single place to decide guest machine types and so.

Note that this patch will slightly change the behavior of aarch64
tests in that previously most vm_create() callers will directly pass
in type==0 into _vm_create() but now the type will depend on
vm_guest_mode, however it shouldn't affect any user because all
vm_create() users of aarch64 will be using VM_MODE_DEFAULT guest
mode (which is VM_MODE_P40V48_4K) so at last type will still be zero.

Reviewed-by: Andrew Jones <drjones@redhat.com>
Signed-off-by: Peter Xu <peterx@redhat.com>
---
 tools/testing/selftests/kvm/dirty_log_test.c  | 13 +++---------
 .../testing/selftests/kvm/include/kvm_util.h  |  3 +--
 tools/testing/selftests/kvm/lib/kvm_util.c    | 21 ++++++++++++-------
 3 files changed, 17 insertions(+), 20 deletions(-)

```
#### [kvm-unit-tests PATCH] travis.yml: Enable running of tests with TCG
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11124443
Return-Path: <SRS0=4maQ=W2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 081C514D5
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 30 Aug 2019 18:45:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E591023428
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 30 Aug 2019 18:45:20 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727959AbfH3SpT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 30 Aug 2019 14:45:19 -0400
Received: from mx1.redhat.com ([209.132.183.28]:52704 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727883AbfH3SpT (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 30 Aug 2019 14:45:19 -0400
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id E19FF300BEA5;
        Fri, 30 Aug 2019 18:45:18 +0000 (UTC)
Received: from thuth.com (unknown [10.36.118.111])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 7609760872;
        Fri, 30 Aug 2019 18:45:14 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: kvm@vger.kernel.org,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Paolo Bonzini <pbonzini@redhat.com>
Cc: David Hildenbrand <david@redhat.com>, Drew Jones <drjones@redhat.com>,
 Laurent Vivier <lvivier@redhat.com>,
 =?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>
Subject: [kvm-unit-tests PATCH] travis.yml: Enable running of tests with TCG
Date: Fri, 30 Aug 2019 20:45:09 +0200
Message-Id: <20190830184509.15240-1-thuth@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.42]);
 Fri, 30 Aug 2019 18:45:18 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Currently the tests at the end of the .travis.yml script are ignored,
since we can not use KVM in the Travis containers. But we can actually
run of some of the kvm-unit-tests with TCG instead, to make sure that
the binaries are not completely broken.
Thus introduce a new TESTS variable that lists the tests which we can
run with TCG. Unfortunately, the ppc64 and s390x QEMUs in Ubuntu also
need some extra love: The ppc64 version only works with the additional
"cap-htm=off" setting. And the s390x package lacks the firmware and
refuses to work unless we provide a fake firmware file here. Any file
works since the firmware is skipped when "-kernel" is used, so we can
simply use one of the pre-existing files in the source tree.

Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 .travis.yml | 19 ++++++++++++++++++-
 1 file changed, 18 insertions(+), 1 deletion(-)

```
#### [PATCH] x86/Hyper-V: Fix overflow issue in the fill_gva_list()
##### From: lantianyu1986@gmail.com

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tianyu Lan <lantianyu1986@gmail.com>
X-Patchwork-Id: 11123011
Return-Path: <SRS0=4maQ=W2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C75CB1800
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 30 Aug 2019 06:15:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A43242186A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 30 Aug 2019 06:15:51 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="Kr+M4nQO"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727054AbfH3GPu (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 30 Aug 2019 02:15:50 -0400
Received: from mail-pg1-f196.google.com ([209.85.215.196]:46690 "EHLO
        mail-pg1-f196.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726452AbfH3GPu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 30 Aug 2019 02:15:50 -0400
Received: by mail-pg1-f196.google.com with SMTP id m3so2968695pgv.13;
        Thu, 29 Aug 2019 23:15:50 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=YekfysBZuovI4KweYbSp+YMJszBxYODg0IxHNTmJQ8E=;
        b=Kr+M4nQOtok8bD8+12TPilMjdoBJsFwAsp+b015vBrQIkrHgWTuAfGUfGHqhNiWeqJ
         pz43SDnYa7KQKzpSTeuTbJEP/EbeDlMZ+sKxIzrdFZQNyKQ2MYGRHSZHo23DWscKbRiC
         0Ip9sxzljSjj3ET6dEINHOdYMZLgrQ/bIDRLT5wi/62jlumgwyzKIkJNPZH+eTaS8BxK
         ra9KGpVzDdAJHeqBbADm5KDZhQzz4WcLqwdWVQeNW9RbiHD3cyUX362exKYIVP8YYvUT
         rORqS2xvu1ZCcJgeU70+tkMaK6zJTfq/Eo+3oYs2ASqHG9+HMfZD6y6hMpEbcP1AlT7g
         iDFA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=YekfysBZuovI4KweYbSp+YMJszBxYODg0IxHNTmJQ8E=;
        b=DNsMWgh/d69y6M8MkTGWW8gGD+zPTa/P/c4xcYJJiaESiyYqq4hbgZc6GA3VVJXwld
         xHSrBjI4pwr1VRxLHp6CvheBTZ7AMEDfkeOTs5D/lk9cYJvPOSWqJdUyyWky3S7CjkUm
         QTTqxSeg1eEh2beUReTqfqvPeCoMG/xYm5626rCTgKZ829glNGjwNyoLvlHr7zvBZn7H
         2efYY9bfUZn8+jbREYgUah5wSZRtcbfiKR/wL8E7l4wipTBMBNvSWSZSD1Fa5M8kcWH6
         FPqaco44c0frwJC8gRI2epundWRB+K5MZC78d1AbOh99dFTndxcmWwS6LQbKB3Oy0ujS
         qXBA==
X-Gm-Message-State: APjAAAXqoQwKwHZQdazhMQnGMtRXl5aeqADmfwTaPQinUsf/GVJd0Pr4
        9aF8o0RyVlnoXm2/epZnkryL/FH6uoA=
X-Google-Smtp-Source: 
 APXvYqwy2fIk8aReh79zAPMFA3zqOX/2l3fVr7CgROjNe57pxsafRfxrGYWtiD4cacLhiz1E8k0eLw==
X-Received: by 2002:a63:3fc9:: with SMTP id
 m192mr11884742pga.429.1567145749714;
        Thu, 29 Aug 2019 23:15:49 -0700 (PDT)
Received: from localhost.corp.microsoft.com ([167.220.255.52])
        by smtp.googlemail.com with ESMTPSA id
 h70sm4291506pgc.36.2019.08.29.23.15.45
        (version=TLS1_2 cipher=ECDHE-RSA-CHACHA20-POLY1305 bits=256/256);
        Thu, 29 Aug 2019 23:15:49 -0700 (PDT)
From: lantianyu1986@gmail.com
X-Google-Original-From: Tianyu.Lan@microsoft.com
To: kys@microsoft.com, haiyangz@microsoft.com, sthemmin@microsoft.com,
        sashal@kernel.org, tglx@linutronix.de, mingo@redhat.com,
        bp@alien8.de, hpa@zytor.com, x86@kernel.org,
        gregkh@linuxfoundation.org, alex.williamson@redhat.com,
        cohuck@redhat.com, michael.h.kelley@microsoft.com
Cc: Tianyu Lan <Tianyu.Lan@microsoft.com>,
        linux-hyperv@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org
Subject: [PATCH] x86/Hyper-V: Fix overflow issue in the fill_gva_list()
Date: Fri, 30 Aug 2019 14:15:40 +0800
Message-Id: <20190830061540.211072-1-Tianyu.Lan@microsoft.com>
X-Mailer: git-send-email 2.14.5
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Tianyu Lan <Tianyu.Lan@microsoft.com>

fill_gva_list() populates gva list and adds offset
HV_TLB_FLUSH_UNIT(0x1000000) to variable "cur"
in the each loop. When diff between "end" and "cur" is
less than HV_TLB_FLUSH_UNIT, the gva entry should
be the last one and the loop should be end.

If cur is equal or greater than 0xFF000000 on 32-bit
mode, "cur" will be overflow after adding HV_TLB_FLUSH_UNIT.
Its value will be wrapped and less than "end". fill_gva_list()
falls into an infinite loop and fill gva list out of
border finally.

Set "cur" to be "end" to make loop end when diff is
less than HV_TLB_FLUSH_UNIT and add HV_TLB_FLUSH_UNIT to
"cur" when diff is equal or greater than HV_TLB_FLUSH_UNIT.
Fix the overflow issue.

Reported-by: Jong Hyun Park <park.jonghyun@yonsei.ac.kr>
Signed-off-by: Tianyu Lan <Tianyu.Lan@microsoft.com>
Fixes: 2ffd9e33ce4a ("x86/hyper-v: Use hypercall for remote
TLB flush")
---
 arch/x86/hyperv/mmu.c | 8 +++++---
 1 file changed, 5 insertions(+), 3 deletions(-)

```
