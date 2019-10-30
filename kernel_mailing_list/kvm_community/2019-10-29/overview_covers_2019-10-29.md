

#### [PATCH v3 0/3] kcov: collect coverage from usb and vhost
##### From: Andrey Konovalov <andreyknvl@google.com>

```c
From patchwork Tue Oct 29 16:32:26 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrey Konovalov <andreyknvl@google.com>
X-Patchwork-Id: 11218139
Return-Path: <SRS0=zizX=YW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5943E1390
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 29 Oct 2019 16:32:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 28F98208E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 29 Oct 2019 16:32:44 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="dnUlLPeH"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2390374AbfJ2Qck (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 29 Oct 2019 12:32:40 -0400
Received: from mail-wr1-f73.google.com ([209.85.221.73]:37721 "EHLO
        mail-wr1-f73.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2390252AbfJ2Qcj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 29 Oct 2019 12:32:39 -0400
Received: by mail-wr1-f73.google.com with SMTP id q14so8813799wrw.4
        for <kvm@vger.kernel.org>; Tue, 29 Oct 2019 09:32:38 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=aFBVvPMXMdVoNWS+arga+zyutc52PrhwrmcehtICP7Y=;
        b=dnUlLPeHrSuhFF3+r3nexRhXSUgG2QFJmbgnM7MsHtu9FFwvUjdpifIlzbNDwRGkd/
         Rugpk2suP1+NWI0NcnbXkosWcp5TC1CcRvDazP+lW6hm5NaO4SXfRFuKQfst1xaVJ735
         loWFY3SBTLlZeW5p5a4BNCH8n5LF1tQy9M5Dcw9+Hx9HDhgklnBWRMOaVr3t+JbGQwPk
         o6f2umBa8YgNSH/0EA9o69e8rdGo1yiXatKJ1mHoKWzbMUsqFfKYyPCdlgB1rnZCCvbE
         ikFEJ8JrBVmn8KZDM/0CUXuDXrNd2ZFJCWCzeVgBfFhqtnbvvxAlQICeYgavC606yNrC
         8ECg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=aFBVvPMXMdVoNWS+arga+zyutc52PrhwrmcehtICP7Y=;
        b=s8gypUmysc8DAMt4VWTU/ASjq4MHBo7mp5uB9PF+fYwmouOvmQibdzvro2xMXcbfHE
         2aUQb54Qo5U1U2aNdj3XM9FpRopDlo+/pJhgEcZr5XtElNXPXfU/RH/oK08g7kg+Do9w
         Y7jfSxXMFm8sk2qer1+hziplfCbCq01TYzNUDygCaVV41JhREN2QDxh9RCkTNu5Ad3mg
         wqRfhiH8n3vWf6j1PShMo/L6RJQdJlcsXL/5w6ewXZRdRowBKhp8kNaUpGB8IQRAWYdy
         Vwc585Q5x+Xmxfm/ulKFAoNHmQ98ZPAYYra7dSMOf8Ekk4zKs3No8iT8zNK+a0mFjVXn
         AkWg==
X-Gm-Message-State: APjAAAVIzvu+NUOjhcbQnaUXOsseXIX3MPeXDFsxeEFU1r88+J7CkVRN
        lQzf778Lo9N57Lb8rqZUxbju4Il4hWSGZt1e
X-Google-Smtp-Source: 
 APXvYqyQYFo/SVqLudHuBq0akKPCDJONWrXAYKTaEfxtfHzCYvYIvxkO/0zufmfXYgX8y9D4iHgx4ShS3grBopTf
X-Received: by 2002:a05:6000:142:: with SMTP id
 r2mr20520344wrx.30.1572366756966;
 Tue, 29 Oct 2019 09:32:36 -0700 (PDT)
Date: Tue, 29 Oct 2019 17:32:26 +0100
Message-Id: <cover.1572366574.git.andreyknvl@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.24.0.rc0.303.g954a862665-goog
Subject: [PATCH v3 0/3] kcov: collect coverage from usb and vhost
From: Andrey Konovalov <andreyknvl@google.com>
To: linux-usb@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        linux-kernel@vger.kernel.org, Dmitry Vyukov <dvyukov@google.com>,
        Greg Kroah-Hartman <gregkh@linuxfoundation.org>,
        Alan Stern <stern@rowland.harvard.edu>,
        "Michael S . Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>
Cc: Andrew Morton <akpm@linux-foundation.org>,
        Arnd Bergmann <arnd@arndb.de>,
        Steven Rostedt <rostedt@goodmis.org>,
        David Windsor <dwindsor@gmail.com>,
        Elena Reshetova <elena.reshetova@intel.com>,
        Anders Roxell <anders.roxell@linaro.org>,
        Alexander Potapenko <glider@google.com>,
        Marco Elver <elver@google.com>,
        Andrey Konovalov <andreyknvl@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset extends kcov to allow collecting coverage from backgound
kernel threads. This extension requires custom annotations for each of the
places where coverage collection is desired. This patchset implements this
for hub events in the USB subsystem and for vhost workers. See the first
patch description for details about the kcov extension. The other two
patches apply this kcov extension to USB and vhost.

Examples of other subsystems that might potentially benefit from this when
custom annotations are added (the list is based on process_one_work()
callers for bugs recently reported by syzbot):
1. fs: writeback wb_workfn() worker,
2. net: addrconf_dad_work()/addrconf_verify_work() workers,
3. net: neigh_periodic_work() worker,
4. net/p9: p9_write_work()/p9_read_work() workers,
5. block: blk_mq_run_work_fn() worker.

These patches have been used to enable coverage-guided USB fuzzing with
syzkaller for the last few years, see the details here:

https://github.com/google/syzkaller/blob/master/docs/linux/external_fuzzing_usb.md

This patchset has been pushed to the public Linux kernel Gerrit instance:

https://linux-review.googlesource.com/c/linux/kernel/git/torvalds/linux/+/1524

Changes v2 -> v3:
- Removed using u64 division as arm can't do that.
- Added EXPORT_SYMBOL() for kcov_common_handle(), kcov_remote_start() and
  kcov_remote_stop().
- Added usage comments for kcov_remote_start(), kcov_remote_stop() and
  kcov_common_handle().
- Expanded a comment in kcov_task_exit() to better explain WARN_ON()
  condition.
- Reduced KCOV_REMOTE_MAX_HANDLES to 0x100 to avoid allowing too many
  GFP_ATOMIC allocations.

Changes v1 -> v2:
- Changed common_handle type back to u64 (to allow extending it in the
  future).
- Reworked kcov_remote_handle() helpers.
- Fixed vhost annotations when CONFIG_KCOV is not enabled.
- Use kcov_disable() instead of kcov_remote_reset() when
  KCOV_REMOTE_ENABLE fails.

Changes RFC v1 -> v1:
- Remove unnecessary #ifdef's from drivers/vhost/vhost.c.
- Reset t->kcov when area allocation fails in kcov_remote_start().
- Use struct_size to calculate array size in kcov_ioctl().
- Add a limit on area_size in kcov_remote_arg.
- Added kcov_disable() helper.
- Changed encoding of kcov remote handle ids, see the documentation.
- Added a comment reference for kcov_sequence task_struct field.
- Change common_handle type to u32.
- Add checks for handle validity into kcov_ioctl_locked() and
    kcov_remote_start().
- Updated documentation to reflect the changes.

Reviewed-by: Dmitry Vyukov <dvyukov@google.com>
Signed-off-by: Andrey Konovalov <andreyknvl@google.com>

Andrey Konovalov (3):
  kcov: remote coverage support
  usb, kcov: collect coverage from hub_event
  vhost, kcov: collect coverage from vhost_worker

 Documentation/dev-tools/kcov.rst | 129 ++++++++
 drivers/usb/core/hub.c           |   5 +
 drivers/vhost/vhost.c            |   6 +
 drivers/vhost/vhost.h            |   1 +
 include/linux/kcov.h             |  23 ++
 include/linux/sched.h            |   8 +
 include/uapi/linux/kcov.h        |  28 ++
 kernel/kcov.c                    | 547 +++++++++++++++++++++++++++++--
 8 files changed, 712 insertions(+), 35 deletions(-)
```
#### [PATCH 0/4] Add support for capturing the highest observable L2 TSC
##### From: Aaron Lewis <aaronlewis@google.com>

```c
From patchwork Tue Oct 29 21:05:51 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Aaron Lewis <aaronlewis@google.com>
X-Patchwork-Id: 11218547
Return-Path: <SRS0=zizX=YW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 27E541390
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 29 Oct 2019 21:06:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E698A21721
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 29 Oct 2019 21:06:06 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="JRcLNfKl"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728121AbfJ2VGF (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 29 Oct 2019 17:06:05 -0400
Received: from mail-pg1-f202.google.com ([209.85.215.202]:46048 "EHLO
        mail-pg1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725840AbfJ2VGF (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 29 Oct 2019 17:06:05 -0400
Received: by mail-pg1-f202.google.com with SMTP id v10so12014900pge.12
        for <kvm@vger.kernel.org>; Tue, 29 Oct 2019 14:06:05 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=IOHjvz17CQBJcXRDm1CfUJG5TnoeR6CvrHThpcD2pHY=;
        b=JRcLNfKlLThQcDKj7JDVFoXkvmsLM+1ynya2CQz8HdtbzDj5Rm1qqOlualkmt6SvnC
         oKvHKoZqoxPExDrloXHW5NPwC1aMAVgKZD0GFsV+idgyrAjXpaAGdNw7u/xjCoOmL8ss
         e9uUVeBhBZFNbe3fGqdOZw7Ce0KDDo1dEycYsGAmoyHqMCc/FBjxLtGoPgN6YZhIRSIZ
         0kl3JvAZpcu0OiYKB5N0i62I6bQjDD/LlNOCNMNIcSIpNikPf7Qyd7ecGHwKnqm6f3Ey
         5xKUD1sC3PQ7ZI7pQHWak+EHsYf0VJP83IrRH1MzT0NBLFYpO4GPj4r3EBLHchDAhq5/
         ULIg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=IOHjvz17CQBJcXRDm1CfUJG5TnoeR6CvrHThpcD2pHY=;
        b=Yom1FnAmzIWzJ9bjea/+VTn94xIrZ8hY2Dl9gdpCncyfJqfWFGWOlu2fENUuJVEn9D
         1+tm06s1j7aWtVHEB60uDtWKFhPZ8ya9UfmTQ3jIlflEoEPSxN3Y2P5RYe5Jz9Hk30E4
         4N4uO4n/XrDYU1TxgtYNhwdLNruF9Af5sO+ciinBI12moelTNgbhZJvIfvFyybDedF/z
         4pv553fX0WHohI6+SbZmbKxvXKQbK41ZxezV2SQwreMmKa55CrdlBcZsTRJxye/JpbZi
         MiYqbkhVmOSvjpGRCjTyK8fXvPMENpoYlxGPfQDixUGu45RUWSDP0v4DdjoZeWC5QYig
         Id8w==
X-Gm-Message-State: APjAAAXEmGskkZcXfKEdvrkGG3yGJYXcmlrwUScMFdPHpoEoI6Sdxg65
        4Ukmm3jjf6SnYcW+a9dQdskzgfS+3x6iiG4JyBVBWZ901/srwyPPTD1Qv6hUz7LPP9eUcgFZ0Ou
        CUMgoJWx+If74XXZmZ0dwpVuNVkPLCc5azTJuQQRoqpxU++GCq18cAlblBS9Y5csf2VSf
X-Google-Smtp-Source: 
 APXvYqwcUGFDYsfoEvI2ABJLun3RY+8ptJ/53Df4lFdCtQg8J67Cw1TZo+Nsul7/D/ELVh8NGhVFGgY1ZWugoy8D
X-Received: by 2002:a63:1042:: with SMTP id 2mr16848851pgq.59.1572383164544;
 Tue, 29 Oct 2019 14:06:04 -0700 (PDT)
Date: Tue, 29 Oct 2019 14:05:51 -0700
Message-Id: <20191029210555.138393-1-aaronlewis@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.24.0.rc0.303.g954a862665-goog
Subject: [PATCH 0/4] Add support for capturing the highest observable L2 TSC
From: Aaron Lewis <aaronlewis@google.com>
To: kvm@vger.kernel.org
Cc: Aaron Lewis <aaronlewis@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The L1 hypervisor may include the IA32_TIME_STAMP_COUNTER MSR in the
vmcs12 MSR VM-exit MSR-store area as a way of determining the highest
TSC value that might have been observed by L2 prior to VM-exit. The
current implementation does not capture a very tight bound on this
value.  To tighten the bound, add the IA32_TIME_STAMP_COUNTER MSR to the
vmcs02 VM-exit MSR-store area whenever it appears in the vmcs12 VM-exit
MSR-store area.  When L0 processes the vmcs12 VM-exit MSR-store area
during the emulation of an L2->L1 VM-exit, special-case the
IA32_TIME_STAMP_COUNTER MSR, using the value stored in the vmcs02
VM-exit MSR-store area to derive the value to be stored in the vmcs12
VM-exit MSR-store area.

Aaron Lewis (4):
  kvm: nested: Introduce read_and_check_msr_entry()
  kvm: vmx: Rename NR_AUTOLOAD_MSRS to NR_MSR_ENTRIES
  kvm: vmx: Rename function find_msr() to vmx_find_msr_index()
  KVM: nVMX: Add support for capturing highest observable L2 TSC

 arch/x86/kvm/vmx/nested.c | 126 ++++++++++++++++++++++++++++++++------
 arch/x86/kvm/vmx/vmx.c    |  14 ++---
 arch/x86/kvm/vmx/vmx.h    |   9 ++-
 3 files changed, 121 insertions(+), 28 deletions(-)
```
