

#### [RESEND v4 0/2] Add bus lock VM exit support
##### From: Chenyi Qiang <chenyi.qiang@intel.com>

```c
From patchwork Mon Oct 12 03:35:40 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Chenyi Qiang <chenyi.qiang@intel.com>
X-Patchwork-Id: 11831535
Return-Path: <SRS0=greB=DT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A6794139F
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 12 Oct 2020 03:33:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9878B20782
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 12 Oct 2020 03:33:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727395AbgJLDdg (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 11 Oct 2020 23:33:36 -0400
Received: from mga04.intel.com ([192.55.52.120]:62770 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727312AbgJLDdd (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 11 Oct 2020 23:33:33 -0400
IronPort-SDR: 
 NCP7zwpDyJfGpqtjqBMPAvrywDOMs2I/4USfx2fjw6CgB1bYwi1JrTEm/mL2ukVoY5VJDrZt/k
 1GWvDpmm0k5A==
X-IronPort-AV: E=McAfee;i="6000,8403,9771"; a="163046217"
X-IronPort-AV: E=Sophos;i="5.77,365,1596524400";
   d="scan'208";a="163046217"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga005.jf.intel.com ([10.7.209.41])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 11 Oct 2020 20:33:31 -0700
IronPort-SDR: 
 I4kBjAynaAr6A8rjDbaP6xW9BLdI7JcpeqY7/MH778QiFWLbJ8RS12E/HvdYKaLk02EziWOFiF
 DQ0MvsYVhM9Q==
X-IronPort-AV: E=Sophos;i="5.77,365,1596524400";
   d="scan'208";a="529780076"
Received: from chenyi-pc.sh.intel.com ([10.239.159.72])
  by orsmga005-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 11 Oct 2020 20:33:28 -0700
From: Chenyi Qiang <chenyi.qiang@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [RESEND v4 0/2] Add bus lock VM exit support
Date: Mon, 12 Oct 2020 11:35:40 +0800
Message-Id: <20201012033542.4696-1-chenyi.qiang@intel.com>
X-Mailer: git-send-email 2.17.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch series add the support for bus lock VM exit in KVM. It is a
sub-feature of bus lock detection. When it is enabled by the VMM, the
processor generates a "Bus Lock" VM exit following execution of an
instruction if the processor detects that one or more bus locks were
caused the instruction was being executed (due to either direct access
by the instruction or stuffed accesses like through A/D updates).

This first patch applies Sean's refactor for vcpu_vmx.exit_reason
available at https://patchwork.kernel.org/patch/11500659.
It is necessary as bus lock VM exit adds a new modifier bit(bit 26) in
exit_reason field in VMCS.

The second patch is the enabling work for bus lock VM exit. Add the
support to set the capability to enable bus lock vm exit. The current
implementation just exit to user space when handling the bus lock
detected in guest.

The concrete throttling policy in user space is still to be discussed.
We can enforce ratelimit on bus lock in guest, inject some sleep time or
maybe other ideas.

Document for Bus Lock Detection is now available at the latest "Intel
Architecture Instruction Set Extensions Programming Reference".

Document Link:
https://software.intel.com/content/www/us/en/develop/download/intel-architecture-instruction-set-extensions-programming-reference.html
---

Changelogs

v3->v4:
- rebase on top of v5.9
- some code cleanup.
- v3:https://lore.kernel.org/lkml/20200910083751.26686-1-chenyi.qiang@intel.com/

v2->v3:
- use a bitmap to get/set the capability of bus lock detection. we support
  exit and off mode currently.
- put the handle of exiting to userspace in vmx.c, thus no need to
  define a shadow to track vmx->exit_reason.bus_lock_detected.
- remove the vcpu->stats.bus_locks since every bus lock exits to userspace.
- v2:https://lore.kernel.org/lkml/20200817033604.5836-1-chenyi.qiang@intel.com/ 

v1->v2:
- resolve Vitaly's comment to introduce the KVM_EXIT_BUS_LOCK and a
  capability to enable it.
- add the support to exit to user space when handling bus locks.
- extend the vcpu->run->flags to indicate bus lock detected for other
  exit reasons when exiting to user space.
- v1:https://lore.kernel.org/lkml/20200628085341.5107-1-chenyi.qiang@intel.com/

---

Chenyi Qiang (1):
  KVM: VMX: Enable bus lock VM exit

Sean Christopherson (1):
  KVM: VMX: Convert vcpu_vmx.exit_reason to a union

 arch/x86/include/asm/kvm_host.h    |   7 ++
 arch/x86/include/asm/vmx.h         |   1 +
 arch/x86/include/asm/vmxfeatures.h |   1 +
 arch/x86/include/uapi/asm/kvm.h    |   1 +
 arch/x86/include/uapi/asm/vmx.h    |   4 +-
 arch/x86/kvm/vmx/capabilities.h    |   6 ++
 arch/x86/kvm/vmx/nested.c          |  42 +++++++-----
 arch/x86/kvm/vmx/vmx.c             | 103 +++++++++++++++++++----------
 arch/x86/kvm/vmx/vmx.h             |  25 ++++++-
 arch/x86/kvm/x86.c                 |  29 +++++++-
 include/uapi/linux/kvm.h           |   5 ++
 11 files changed, 172 insertions(+), 52 deletions(-)
```
#### [PATCH v3 0/4] Test MSR exits to userspace
##### From: Aaron Lewis <aaronlewis@google.com>

```c
From patchwork Mon Oct 12 19:47:12 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Aaron Lewis <aaronlewis@google.com>
X-Patchwork-Id: 11833651
Return-Path: <SRS0=greB=DT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 662341592
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 12 Oct 2020 19:47:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 405CB20735
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 12 Oct 2020 19:47:35 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="qP5M0MyX"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2391443AbgJLTre (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 12 Oct 2020 15:47:34 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:59880 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2391413AbgJLTrd (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 12 Oct 2020 15:47:33 -0400
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id E063DC0613D0
        for <kvm@vger.kernel.org>; Mon, 12 Oct 2020 12:47:31 -0700 (PDT)
Received: by mail-yb1-xb4a.google.com with SMTP id x1so18693708ybi.4
        for <kvm@vger.kernel.org>; Mon, 12 Oct 2020 12:47:31 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=DWoogOPzifjrjox3Xp7XZd0Vq+PlvblBZZlxSc6Gj2U=;
        b=qP5M0MyXRz61ZFFuMWYy5rOqtxjbMNIoQjkMmZdjAWsC/zgueYE0qYe+3wbpJehQ9Y
         pQiRNNpcCHHhhaeIOBBvWk4T+tSHVCTU4lcLZ96Z3vwA8rK8f03FnNnnRUB4NNJ0nZ4l
         O4jhgQmZpAs4Du1VjoBsD+mK+CA07J7Mjq/hUB8f9JyWW3TmjqICdemCXIX2hCJelHu/
         MHhzmIE9VysB8JrJ8/4U8F+pmYTi7UDIVGi7oCOOAk01mN7SvjGlhRigQRiLWlujZToh
         TX84Z+OXWlN8STPCZ47CtGEM7cD6+koilEA0XdEHrtyaN6D0WlmyYS3WcyL+SPBQAuoM
         M+gQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=DWoogOPzifjrjox3Xp7XZd0Vq+PlvblBZZlxSc6Gj2U=;
        b=Ig0jmMicqEl+oN58rHKEjVKJMLf5DCIg403WjeOuoRC4F+zKJfGklD8rWFSeq47Yko
         ttR+UjDIA4RUdieyJpuzKEZ/cPShpkDHu9L1i+U/Ivgt3dwL3Fr30r1tV4HFBLtvSh0b
         oR6R81vNt85a12ItrC/fOjAXDK1V/SGMEROdln4aNCPejsbcd1Off2PoriBJYrpjXogH
         DldBc52uW0sugBMEmpIdTuJg+lTmcRtK6xKU9hZQbey9vwCf5/uSNTO55yDKH7K/JyAF
         g0Q3G1aBCQqWIw6gE/ZEWrpWAqVeCYxBYgE6EqrMVj6Np9yN6wvrbABuxkY9VMvvFU7Z
         UHOQ==
X-Gm-Message-State: AOAM531ycb+oMYwjnQja11GjSpgu74JTAufFvGKHcv8kQIYx8kUk5PS3
        SSs9JXp2bYFncYwgxh1p9fz/wznjb0kXraGG
X-Google-Smtp-Source: 
 ABdhPJzwxsa35ENsFO6q9F8B619B8tLXLcvgCJycFYM8H4NfkvXJbHMJx8MfWzhsJS3osiKLfVWM6I69Kptm103A
Sender: "aaronlewis via sendgmr" <aaronlewis@aaronlewis1.sea.corp.google.com>
X-Received: from aaronlewis1.sea.corp.google.com
 ([2620:15c:100:202:a28c:fdff:fed8:8d46])
 (user=aaronlewis job=sendgmr) by 2002:a05:6902:1025:: with SMTP id
 x5mr32983524ybt.131.1602532050999; Mon, 12 Oct 2020 12:47:30 -0700 (PDT)
Date: Mon, 12 Oct 2020 12:47:12 -0700
Message-Id: <20201012194716.3950330-1-aaronlewis@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.28.0.1011.ga647a8990f-goog
Subject: [PATCH v3 0/4] Test MSR exits to userspace
From: Aaron Lewis <aaronlewis@google.com>
To: graf@amazon.com
Cc: pshier@google.com, jmattson@google.com, kvm@vger.kernel.org,
        Aaron Lewis <aaronlewis@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset adds additional testing to the series ("Allow user space to
restrict and augment MSR emulation") by Alexander Graf <graf@amazon.com>,
and supliments the selftest in that series.

This patchset introduces exception handling into the kvm selftest framework
which is then used in the test to be able to handle #GPs that are injected
into the guest from userspace.

The test focuses on two main areas:
  1) It tests the MSR filter API.
  2) It tests MSR permission bitmaps.

v1 -> v2:

  - Use exception_handlers instead of gs base to pass table to the guest.
  - Move unexpected vector assert to processor.c.

v2 -> v3:

  - Add stubs for assert_on_unhandled_exception() in aarch64 and s390x.

Aaron Lewis (4):
  selftests: kvm: Fix the segment descriptor layout to match the actual
    layout
  selftests: kvm: Clear uc so UCALL_NONE is being properly reported
  selftests: kvm: Add exception handling to selftests
  selftests: kvm: Test MSR exiting to userspace

 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |  20 +-
 .../testing/selftests/kvm/include/kvm_util.h  |   2 +
 .../selftests/kvm/include/x86_64/processor.h  |  26 +-
 .../selftests/kvm/lib/aarch64/processor.c     |   4 +
 .../testing/selftests/kvm/lib/aarch64/ucall.c |   3 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |   5 +
 .../selftests/kvm/lib/kvm_util_internal.h     |   2 +
 .../selftests/kvm/lib/s390x/processor.c       |   4 +
 tools/testing/selftests/kvm/lib/s390x/ucall.c |   3 +
 .../selftests/kvm/lib/x86_64/handlers.S       |  81 +++
 .../selftests/kvm/lib/x86_64/processor.c      | 117 +++-
 .../testing/selftests/kvm/lib/x86_64/ucall.c  |   3 +
 .../kvm/x86_64/userspace_msr_exit_test.c      | 560 ++++++++++++++++++
 14 files changed, 820 insertions(+), 11 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/lib/x86_64/handlers.S
 create mode 100644 tools/testing/selftests/kvm/x86_64/userspace_msr_exit_test.c
```
