

#### [PATCH 0/8] KVM: nSVM: ondemand nested state allocation + nested
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
From patchwork Thu Aug 20 09:13:19 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 11725945
Return-Path: <SRS0=1nBL=B6=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6F238739
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Aug 2020 09:13:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 55A6520885
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Aug 2020 09:13:45 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="fuo/QEJu"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726836AbgHTJNk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 20 Aug 2020 05:13:40 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:39752 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726819AbgHTJNh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 20 Aug 2020 05:13:37 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1597914816;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=A3aFtdgeFbcYR03wKrWlf344PhwxLiPdlKO9qqCpcnY=;
        b=fuo/QEJuz+YkSDag8JooAPqlkwvrfGQPu2hSCGSI6zDV3dQH5WSKGnVfNTHxDtSxoiXmYo
        X9KLfksQ99KlNSI741yot/L60y6zzlvztrzFnKss7QMGYORnt6PGUiCs/NO/mmNyBtnjgV
        7BJZhpDC72YWTmaHlnu17se449eT95M=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-497-zyT1cK7ZMwSTsNDtTeLzcw-1; Thu, 20 Aug 2020 05:13:34 -0400
X-MC-Unique: zyT1cK7ZMwSTsNDtTeLzcw-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B72B4425D2;
        Thu, 20 Aug 2020 09:13:32 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.173])
        by smtp.corp.redhat.com (Postfix) with ESMTP id BEBE27E309;
        Thu, 20 Aug 2020 09:13:28 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Jim Mattson <jmattson@google.com>, Joerg Roedel <joro@8bytes.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Borislav Petkov <bp@alien8.de>,
        Thomas Gleixner <tglx@linutronix.de>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        linux-kernel@vger.kernel.org (open list:X86 ARCHITECTURE (32-BIT AND
        64-BIT)),
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Ingo Molnar <mingo@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH 0/8] KVM: nSVM: ondemand nested state allocation + nested
 guest state caching
Date: Thu, 20 Aug 2020 12:13:19 +0300
Message-Id: <20200820091327.197807-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi!

This patch series implements caching of the whole nested guest vmcb
as opposed to current code that only caches its control area.
This allows us to avoid race in which guest changes the data area
while we are verifying it.

In adddition to that I also implemented on demand nested state area
to compensate a bit for memory usage increase from this caching.
This way at least guests that don't use nesting won't waste memory
on nested state.

Patches 1,2,3 are just refactoring,

Patches 4,5 are for ondemand nested state, while patches 6,7,8 are
for caching of the nested state.

Patch 8 is more of an optimization and can be dropped if you like to.

The series was tested with various nested guests, in one case even with
L3 running, but note that due to unrelated issue, migration with nested
guest running didn't work for me with or without this series.
I am investigating this currently.

Best regards,
	Maxim Levitsky

Maxim Levitsky (8):
  KVM: SVM: rename a variable in the svm_create_vcpu
  KVM: nSVM: rename nested 'vmcb' to vmcb_gpa in few places
  KVM: SVM: refactor msr permission bitmap allocation
  KVM: x86: allow kvm_x86_ops.set_efer to return a value
  KVM: nSVM: implement ondemand allocation of the nested state
  SVM: nSVM: cache whole nested vmcb instead of only its control area
  KVM: nSVM: implement caching of nested vmcb save area
  KVM: nSVM: read only changed fields of the nested guest data area

 arch/x86/include/asm/kvm_host.h |   2 +-
 arch/x86/kvm/svm/nested.c       | 296 +++++++++++++++++++++++---------
 arch/x86/kvm/svm/svm.c          | 129 +++++++-------
 arch/x86/kvm/svm/svm.h          |  32 ++--
 arch/x86/kvm/vmx/vmx.c          |   5 +-
 arch/x86/kvm/x86.c              |   3 +-
 6 files changed, 312 insertions(+), 155 deletions(-)
```
#### [PATCH v2 0/7] KVM: nSVM: ondemand nested state allocation + smm
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
From patchwork Thu Aug 20 13:33:32 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 11726327
Return-Path: <SRS0=1nBL=B6=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 28A5B739
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Aug 2020 13:37:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 100FD22B43
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Aug 2020 13:37:13 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="FgUxwuIm"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729070AbgHTNhL (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 20 Aug 2020 09:37:11 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:28019 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1729663AbgHTNd7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 20 Aug 2020 09:33:59 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1597930437;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=X2fJCEf/hhnmDqCnQtY5hjOcNe8YUPEVscVUU8eAkMY=;
        b=FgUxwuImrHXMEeBy5azRmZsROXuXDEEzkyOt3QmFHc6HukJHlqW1Tt7LCRCo7rWmfaAaJW
        rDUNrSJRIdxHiy+wQe/31PsyKJGwR/Ny7aLW0S9Tke5+1VgRKw45xxQYkd9m0tWa/bW1pi
        vNvh1NI8AfRThKGysUcsxlUo8MprPfE=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-196-vDgPCg3fNbqGSmAdSCx5vQ-1; Thu, 20 Aug 2020 09:33:46 -0400
X-MC-Unique: vDgPCg3fNbqGSmAdSCx5vQ-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B2A52AE641;
        Thu, 20 Aug 2020 13:33:43 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.173])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 35F7219D6C;
        Thu, 20 Aug 2020 13:33:40 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Jim Mattson <jmattson@google.com>,
        Ingo Molnar <mingo@redhat.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        linux-kernel@vger.kernel.org (open list:X86 ARCHITECTURE (32-BIT AND
        64-BIT)), "H. Peter Anvin" <hpa@zytor.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Joerg Roedel <joro@8bytes.org>,
        Wanpeng Li <wanpengli@tencent.com>,
        Borislav Petkov <bp@alien8.de>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH v2 0/7] KVM: nSVM: ondemand nested state allocation + smm
 fixes
Date: Thu, 20 Aug 2020 16:33:32 +0300
Message-Id: <20200820133339.372823-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi!

This patch series does some refactoring and implements on demand nested state area
This way at least guests that don't use nesting won't waste memory
on nested state.

Patches 1,2,3 are refactoring

Patches 4,5 are new from V1 and implement more strict SMM save state area checking
on resume from SMM to avoid guest tampering with this area.

This was done to avoid crashing if the guest enabled 'guest was interrupted'
flag there and we don't have nested state allocated.

Patches 6,7 are for ondemand nested state.

The series was tested with various nested guests, in one case even with
L3 running, but note that due to unrelated issue, migration with nested
guest running didn't work for me with or without this series.
I am investigating this currently.

Best regards,
	Maxim Levitsky

Maxim Levitsky (7):
  KVM: SVM: rename a variable in the svm_create_vcpu
  KVM: nSVM: rename nested 'vmcb' to vmcb12_gpa in few places
  KVM: SVM: refactor msr permission bitmap allocation
  KVM: x86: allow kvm_x86_ops.set_efer to return a value
  KVM: nSVM: more strict smm checks
  KVM: emulator: more strict rsm checks.
  KVM: nSVM: implement ondemand allocation of the nested state

 arch/x86/include/asm/kvm_host.h |   2 +-
 arch/x86/kvm/emulate.c          |  22 ++++--
 arch/x86/kvm/svm/nested.c       |  53 +++++++++++--
 arch/x86/kvm/svm/svm.c          | 130 ++++++++++++++++++--------------
 arch/x86/kvm/svm/svm.h          |  10 ++-
 arch/x86/kvm/vmx/vmx.c          |   5 +-
 arch/x86/kvm/x86.c              |   3 +-
 7 files changed, 151 insertions(+), 74 deletions(-)
```
