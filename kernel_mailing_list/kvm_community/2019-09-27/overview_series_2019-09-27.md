#### [kvm-unit-tests PATCH 1/6] arm: gic: check_acked: add test description
##### From: Andre Przywara <andre.przywara@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andre Przywara <andre.przywara@arm.com>
X-Patchwork-Id: 11164329
Return-Path: <SRS0=cTVl=XW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 48954924
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Sep 2019 10:42:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 319F921906
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Sep 2019 10:42:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726163AbfI0Kmh (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 27 Sep 2019 06:42:37 -0400
Received: from foss.arm.com ([217.140.110.172]:48728 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725946AbfI0Kmg (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 27 Sep 2019 06:42:36 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id F00FE142F;
        Fri, 27 Sep 2019 03:42:34 -0700 (PDT)
Received: from donnerap.arm.com (donnerap.cambridge.arm.com [10.1.197.44])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 2F9893F534;
        Fri, 27 Sep 2019 03:42:34 -0700 (PDT)
From: Andre Przywara <andre.przywara@arm.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Andrew Jones <drjones@redhat.com>
Cc: kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org
Subject: [kvm-unit-tests PATCH 1/6] arm: gic: check_acked: add test
 description
Date: Fri, 27 Sep 2019 11:42:22 +0100
Message-Id: <20190927104227.253466-2-andre.przywara@arm.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20190927104227.253466-1-andre.przywara@arm.com>
References: <20190927104227.253466-1-andre.przywara@arm.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

At the moment the check_acked() IRQ helper function just prints a
generic "Completed" or "Timed out" message, without given a more
detailed test description.

To be able to tell the different IRQ tests apart, and also to allow
re-using it more easily, add a "description" parameter string,
which is prefixing the output line. This gives more information on what
exactly was tested.

This also splits the variable output part of the line (duration of IRQ
delivery) into a separate INFO: line, to not confuse testing frameworks.

Signed-off-by: Andre Przywara <andre.przywara@arm.com>
---
 arm/gic.c | 17 ++++++++++-------
 1 file changed, 10 insertions(+), 7 deletions(-)

```
#### [PATCH 1/9] KVM: selftests: Create a demand paging testFrom: Ben Gardon <bgardon@google.com>
##### From: Ben Gardon <bgardon@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ben Gardon <bgardon@google.com>
X-Patchwork-Id: 11164795
Return-Path: <SRS0=cTVl=XW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3A17F112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Sep 2019 16:18:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0331B217D9
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Sep 2019 16:18:45 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="ULK6gXR8"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728031AbfI0QSo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 27 Sep 2019 12:18:44 -0400
Received: from mail-pl1-f202.google.com ([209.85.214.202]:36684 "EHLO
        mail-pl1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727472AbfI0QSn (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 27 Sep 2019 12:18:43 -0400
Received: by mail-pl1-f202.google.com with SMTP id z7so1930745plo.3
        for <kvm@vger.kernel.org>; Fri, 27 Sep 2019 09:18:42 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=qJ+LEDwdF8ZWMIEms9IYF0Bd8vnOKy8mjBBE8Ycu9gw=;
        b=ULK6gXR8q5rgcooUN6wDCQ/pTf8NwdYYNiCy6cjbhuIS2ezT7GYhy4/vgE6FmnUTT1
         5MKcEh7fxqwQTWAXTn6Tb3by3YE7WT6BqXILzo8gUcn7Gq/gi98/7rCkJ1xA3eT0BkBl
         F0p+s2CJRCH+Wjvwe0/neMzuCKEU/y5TGLfXTu3jHInGwvMO64M9kcWVjDfgtY/+PtfW
         9w0R1qYc4ptK58lSQDf1kswZnH2JSKge/V05b52rbzv+8mmt5kYbQ8byAUAXH1TNS4qj
         CVJdLKin//zcp3c0Q7jJP9k2yKtproIqzwidaWKR+cEgsN3/vZNULxQluLmjU1Cld6k8
         ekXw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=qJ+LEDwdF8ZWMIEms9IYF0Bd8vnOKy8mjBBE8Ycu9gw=;
        b=Y4E+FUrOHwtdHTvjmASijCwl6cPC1IEKvxX6tvTh9rZy74MMyh7fxrNiiBSx0IoJIj
         qmvFE+emyEN3UtbwCRshUvOSxrHVVJlwV4AzyHsl2w547ScaKf8M3CQJV6+vUfsrD75r
         h7KkbAMCMP0gisQ5TYhHcfJBmhvo1+15TJcceeUkmFMg+jzj8mT1aR3mXdIb56ryG2KW
         NsFs8ouAFBjDcr3/GVnt4PCbFtl5ZEaOLGAYBDLuiWJRS9SBpHZKJT3A2RRwSgDqPqNj
         ms1KXOlmEsUfizXPRtOuNR7mYZhVGi6LQ0o7v9q95YNz5ksmWFYmPgWWVybzM8WWHDyR
         zqqg==
X-Gm-Message-State: APjAAAUxXCHIArDTV4DaLvrXvZpY2ZksTTyYC4db87Vb+4El4JE9cmcc
        Vq+NhzfsGmhRIoqjr38EgdpTFCyd4VYzTSjlFn+VpmO5Q0PKKkOxfW/Ump8fT/iuDXNeQbTrrvk
        xa7/pvXm82HjuePwYqYI8XO/A3m5OVBN8oDjDkrmd9qJsaRVGMXZYQe3a9mU2
X-Google-Smtp-Source: 
 APXvYqxds/SzjvGjI/EquH8fe9HqsqZXZoJ2mRqpd9OwXaJvs5LhfB82U2/4JSofrqKajWDxvoPV2iM2gfIn
X-Received: by 2002:a63:d343:: with SMTP id u3mr10192159pgi.313.1569601122074;
 Fri, 27 Sep 2019 09:18:42 -0700 (PDT)
Date: Fri, 27 Sep 2019 09:18:29 -0700
In-Reply-To: <20190927161836.57978-1-bgardon@google.com>
Message-Id: <20190927161836.57978-2-bgardon@google.com>
Mime-Version: 1.0
References: <20190927161836.57978-1-bgardon@google.com>
X-Mailer: git-send-email 2.23.0.444.g18eeb5a265-goog
Subject: [PATCH 1/9] KVM: selftests: Create a demand paging test
From: Ben Gardon <bgardon@google.com>
To: kvm@vger.kernel.org, linux-kselftest@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Cannon Matthews <cannonmatthews@google.com>,
        Peter Xu <peterx@redhat.com>,
        Andrew Jones <drjones@redhat.com>,
        Ben Gardon <bgardon@google.com>
Content-Type: text/plain; charset="UTF-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

While userfaultfd, KVM's demand paging implementation, is not specific
to KVM, having a benchmark for its performance will be useful for
guiding performance improvements to KVM. As a first step towards creating
a userfaultfd demand paging test, create a simple memory access test,
based on dirty_log_test.

Signed-off-by: Ben Gardon <bgardon@google.com>
---
 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   2 +
 .../selftests/kvm/demand_paging_test.c        | 286 ++++++++++++++++++
 3 files changed, 289 insertions(+)
 create mode 100644 tools/testing/selftests/kvm/demand_paging_test.c

```
#### [PATCH] docs: use flexible array members, not zero-length
##### From: Stephen Kitt <steve@sk2.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stephen Kitt <steve@sk2.org>
X-Patchwork-Id: 11164643
Return-Path: <SRS0=cTVl=XW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F034C14DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Sep 2019 14:38:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C01EC217D7
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Sep 2019 14:38:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727421AbfI0Oim (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 27 Sep 2019 10:38:42 -0400
Received: from 3.mo69.mail-out.ovh.net ([188.165.52.203]:45386 "EHLO
        3.mo69.mail-out.ovh.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726540AbfI0Oim (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 27 Sep 2019 10:38:42 -0400
X-Greylist: delayed 474 seconds by postgrey-1.27 at vger.kernel.org;
 Fri, 27 Sep 2019 10:38:39 EDT
Received: from player687.ha.ovh.net (unknown [10.108.57.49])
        by mo69.mail-out.ovh.net (Postfix) with ESMTP id 8B2B16B067
        for <kvm@vger.kernel.org>; Fri, 27 Sep 2019 16:30:43 +0200 (CEST)
Received: from sk2.org (unknown [65.39.69.237])
        (Authenticated sender: steve@sk2.org)
        by player687.ha.ovh.net (Postfix) with ESMTPSA id 7A2E5A476CBE;
        Fri, 27 Sep 2019 14:30:32 +0000 (UTC)
From: Stephen Kitt <steve@sk2.org>
To: linux-doc@vger.kernel.org
Cc: corbet@lwn.net, bpf@vger.kernel.org, linux-kernel@vger.kernel.org,
        linux-remoteproc@vger.kernel.org, linux-can@vger.kernel.org,
        linux-afs@lists.infradead.org, kvm@vger.kernel.org,
        Stephen Kitt <steve@sk2.org>,
        "Gustavo A . R . Silva" <gustavo@embeddedor.com>
Subject: [PATCH] docs: use flexible array members, not zero-length
Date: Fri, 27 Sep 2019 16:29:27 +0200
Message-Id: <20190927142927.27968-1-steve@sk2.org>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-Ovh-Tracer-Id: 2095018254973357452
X-VR-SPAMSTATE: OK
X-VR-SPAMSCORE: -100
X-VR-SPAMCAUSE: 
 gggruggvucftvghtrhhoucdtuddrgedufedrfeeigdejiecutefuodetggdotefrodftvfcurfhrohhfihhlvgemucfqggfjpdevjffgvefmvefgnecuuegrihhlohhuthemucehtddtnecusecvtfgvtghiphhivghnthhsucdlqddutddtmd
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Update the docs throughout to remove zero-length arrays, replacing
them with C99 flexible array members. GCC will then ensure that the
arrays are always the last element in the struct.

Signed-off-by: Stephen Kitt <steve@sk2.org>
Cc: Gustavo A. R. Silva <gustavo@embeddedor.com>
---
 Documentation/bpf/btf.rst                     |  2 +-
 Documentation/digsig.txt                      |  4 ++--
 Documentation/driver-api/connector.rst        |  2 +-
 Documentation/driver-api/usb/URB.rst          |  2 +-
 .../filesystems/autofs-mount-control.txt      |  2 +-
 Documentation/filesystems/autofs.txt          |  2 +-
 Documentation/filesystems/fiemap.txt          |  2 +-
 Documentation/hwspinlock.txt                  |  2 +-
 Documentation/networking/can.rst              |  2 +-
 Documentation/networking/rxrpc.txt            |  2 +-
 Documentation/remoteproc.txt                  |  4 ++--
 Documentation/virt/kvm/api.txt                | 24 +++++++++----------
 Documentation/x86/boot.rst                    |  4 ++--
 13 files changed, 27 insertions(+), 27 deletions(-)

```
#### [GIT PULL] Second batch of KVM changes for Linux 5.4 merge window
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11164429
Return-Path: <SRS0=cTVl=XW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7FCAC76
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Sep 2019 12:08:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 542F221848
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Sep 2019 12:08:11 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="T5eYcciS"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727076AbfI0MII (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 27 Sep 2019 08:08:08 -0400
Received: from mail-wr1-f67.google.com ([209.85.221.67]:45718 "EHLO
        mail-wr1-f67.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726163AbfI0MIH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 27 Sep 2019 08:08:07 -0400
Received: by mail-wr1-f67.google.com with SMTP id r5so2416537wrm.12;
        Fri, 27 Sep 2019 05:08:05 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=z7/9s3BxxTpVOqUwSt5oErpICTF5+R9LsJXWbH8WU0Y=;
        b=T5eYcciSYy0hl1Z3CnsZPxVGZem+Tg/HkVuXzq/KvwM/AFoescyYYw6r1WB3gI/lFe
         GWcyFvru3jp/UEvNxbN/TDMDjlxejjh+vuoCqWp4UERerKMVpoEWz4YlHC39zTdo9eYD
         NC6I/kUXSWjRqFN/g8aOZZ/jGFuDmcVY4m+/LxQ5SSk896hDefx82NfIVAUcksYi6rIW
         QOXsylaw7hk7tVw6Sh/mGDFtgz4xbdYwZSo9yo6nezYWGpiLg9FYJ0Dgx4VOawdQYvi9
         dftyEs3q8F7yx+cdzlW/AmveYCSnCjWCGmvPyQbo0Jj9fEQ7ICrD3kuF/RJzT3WgMD0+
         ZCsQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=z7/9s3BxxTpVOqUwSt5oErpICTF5+R9LsJXWbH8WU0Y=;
        b=PKB0r5JkfPamoHyr6lmr798+HVdCAhEG3ezsVxfvIU9vYgRwQ0hIffO3w6O43cIn12
         /vc45QlghSbgAOIkEsNFZQxTd1iHiguWqzkepjWynivBG74YXwY9fAv+ZKfOVj9fD1tY
         K6RRCfo84dD7a95H0O6komUOT4OoI0q5/htZCVQhFUNNf3reH1I6G43h0XhCBT2BOESA
         u18/HO8P6p3tujxAep4Pd9HbZ3RJgFMEfWYwR7b4K3HakoJ5wHeOsUthd7GZRR1nfZls
         Doz43Lea7tK6/D1iPC7feGmCkmazkTOvr46/ECGOK58DLEWNFUU4ZrmIDqeSUbaPUAO1
         +EWA==
X-Gm-Message-State: APjAAAUpTf+lOFNQ9ji61e0lI/ui20lk8yIJ2n4Hpzuvo9jJYyHbU0Xa
        3CJEDBPPfOl96XS2qwTl9jQvBelM
X-Google-Smtp-Source: 
 APXvYqw+xZvHs7FtPH3B/HBeRf5/Du++X8PfFvrm/lhIDVT+mM4s/DjbTVi4oRpmjBGenbqbu2SWlw==
X-Received: by 2002:adf:e612:: with SMTP id p18mr2623213wrm.218.1569586084352;
        Fri, 27 Sep 2019 05:08:04 -0700 (PDT)
Received: from 640k.lan ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 o188sm9540223wma.14.2019.09.27.05.08.02
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Fri, 27 Sep 2019 05:08:03 -0700 (PDT)
From: Paolo Bonzini <pbonzini@redhat.com>
To: torvalds@linux-foundation.org
Cc: linux-kernel@vger.kernel.org, rkrcmar@redhat.com,
        kvm@vger.kernel.org
Subject: [GIT PULL] Second batch of KVM changes for Linux 5.4 merge window
Date: Fri, 27 Sep 2019 14:08:02 +0200
Message-Id: <1569586082-13995-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linus,

The following changes since commit 4c07e2ddab5b6b57dbcb09aedbda1f484d5940cc:

  Merge tag 'mfd-next-5.4' of git://git.kernel.org/pub/scm/linux/kernel/git/lee/mfd (2019-09-23 19:37:49 -0700)

are available in the git repository at:


  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to fd3edd4a9066f28de99a16685a586d68a9f551f8:

  KVM: nVMX: cleanup and fix host 64-bit mode checks (2019-09-25 19:22:33 +0200)

----------------------------------------------------------------
x86 KVM changes:
* The usual accuracy improvements for nested virtualization
* The usual round of code cleanups from Sean
* Added back optimizations that were prematurely removed in 5.2
  (the bare minimum needed to fix the regression was in 5.3-rc8,
  here comes the rest)
* Support for UMWAIT/UMONITOR/TPAUSE
* Direct L2->L0 TLB flushing when L0 is Hyper-V and L1 is KVM
* Tell Windows guests if SMT is disabled on the host
* More accurate detection of vmexit cost
* Revert a pvqspinlock pessimization

----------------------------------------------------------------
Jim Mattson (3):
      kvm: x86: Add Intel PMU MSRs to msrs_to_save[]
      kvm: x86: Add "significant index" flag to a few CPUID leaves
      kvm: svm: Intercept RDPRU

Krish Sadhukhan (1):
      KVM: nVMX: Check Host Address Space Size on vmentry of nested guests

Marc Orr (1):
      kvm: nvmx: limit atomic switch MSRs

Paolo Bonzini (1):
      KVM: nVMX: cleanup and fix host 64-bit mode checks

Peter Xu (4):
      KVM: selftests: Move vm type into _vm_create() internally
      KVM: selftests: Create VM earlier for dirty log test
      KVM: selftests: Introduce VM_MODE_PXXV48_4K
      KVM: selftests: Remove duplicate guest mode handling

Sean Christopherson (30):
      KVM: x86: Manually flush collapsible SPTEs only when toggling flags
      KVM: x86: Relocate MMIO exit stats counting
      KVM: x86: Clean up handle_emulation_failure()
      KVM: x86: Refactor kvm_vcpu_do_singlestep() to remove out param
      KVM: x86: Don't attempt VMWare emulation on #GP with non-zero error code
      KVM: x86: Move #GP injection for VMware into x86_emulate_instruction()
      KVM: x86: Add explicit flag for forced emulation on #UD
      KVM: x86: Move #UD injection for failed emulation into emulation code
      KVM: x86: Exit to userspace on emulation skip failure
      KVM: x86: Handle emulation failure directly in kvm_task_switch()
      KVM: x86: Move triple fault request into RM int injection
      KVM: VMX: Remove EMULATE_FAIL handling in handle_invalid_guest_state()
      KVM: x86: Remove emulation_result enums, EMULATE_{DONE,FAIL,USER_EXIT}
      KVM: VMX: Handle single-step #DB for EMULTYPE_SKIP on EPT misconfig
      KVM: x86: Add comments to document various emulation types
      KVM: x86/mmu: Treat invalid shadow pages as obsolete
      KVM: x86/mmu: Use fast invalidate mechanism to zap MMIO sptes
      KVM: x86/mmu: Revert "Revert "KVM: MMU: show mmu_valid_gen in shadow page related tracepoints""
      KVM: x86/mmu: Revert "Revert "KVM: MMU: add tracepoint for kvm_mmu_invalidate_all_pages""
      KVM: x86/mmu: Revert "Revert "KVM: MMU: zap pages in batch""
      KVM: x86/mmu: Revert "Revert "KVM: MMU: collapse TLB flushes when zap all pages""
      KVM: x86/mmu: Revert "Revert "KVM: MMU: reclaim the zapped-obsolete page first""
      KVM: x86/mmu: Revert "KVM: x86/mmu: Remove is_obsolete() call"
      KVM: x86/mmu: Explicitly track only a single invalid mmu generation
      KVM: x86/mmu: Skip invalid pages during zapping iff root_count is zero
      KVM: x86: Check kvm_rebooting in kvm_spurious_fault()
      KVM: VMX: Optimize VMX instruction error and fault handling
      KVM: VMX: Add error handling to VMREAD helper
      KVM: x86: Drop ____kvm_handle_fault_on_reboot()
      KVM: x86: Don't check kvm_rebooting in __kvm_handle_fault_on_reboot()

Tao Xu (3):
      KVM: x86: Add support for user wait instructions
      KVM: vmx: Emulate MSR IA32_UMWAIT_CONTROL
      KVM: vmx: Introduce handle_unexpected_vmexit and handle WAITPKG vmexit

Tianyu Lan (2):
      x86/Hyper-V: Fix definition of struct hv_vp_assist_page
      KVM/Hyper-V: Add new KVM capability KVM_CAP_HYPERV_DIRECT_TLBFLUSH

Vitaly Kuznetsov (8):
      KVM/Hyper-V/VMX: Add direct tlb flush support
      KVM: x86: svm: remove unneeded nested_enable_evmcs() hook
      KVM: x86: announce KVM_CAP_HYPERV_ENLIGHTENED_VMCS support only when it is available
      cpu/SMT: create and export cpu_smt_possible()
      KVM: x86: hyper-v: set NoNonArchitecturalCoreSharing CPUID bit when SMT is impossible
      KVM: selftests: hyperv_cpuid: add check for NoNonArchitecturalCoreSharing bit
      KVM: selftests: fix ucall on x86
      KVM: vmx: fix build warnings in hv_enable_direct_tlbflush() on i386

Wanpeng Li (3):
      KVM: hyperv: Fix Direct Synthetic timers assert an interrupt w/o lapic_in_kernel
      KVM: LAPIC: Tune lapic_timer_advance_ns smoothly
      Revert "locking/pvqspinlock: Don't wait if vCPU is preempted"

 Documentation/virt/kvm/api.txt                     |  13 +
 arch/x86/include/asm/hyperv-tlfs.h                 |  31 ++-
 arch/x86/include/asm/kvm_host.h                    |  64 +++--
 arch/x86/include/asm/svm.h                         |   1 +
 arch/x86/include/asm/vmx.h                         |   2 +
 arch/x86/include/uapi/asm/svm.h                    |   1 +
 arch/x86/include/uapi/asm/vmx.h                    |   6 +-
 arch/x86/kernel/cpu/umwait.c                       |   6 +
 arch/x86/kvm/cpuid.c                               |   8 +-
 arch/x86/kvm/hyperv.c                              |  16 +-
 arch/x86/kvm/lapic.c                               |  28 +-
 arch/x86/kvm/lapic.h                               |   1 -
 arch/x86/kvm/mmu.c                                 | 145 +++++-----
 arch/x86/kvm/mmutrace.h                            |  42 ++-
 arch/x86/kvm/svm.c                                 |  79 +++---
 arch/x86/kvm/vmx/capabilities.h                    |   6 +
 arch/x86/kvm/vmx/evmcs.h                           |   2 +
 arch/x86/kvm/vmx/nested.c                          |  70 ++++-
 arch/x86/kvm/vmx/ops.h                             |  93 ++++---
 arch/x86/kvm/vmx/vmx.c                             | 306 ++++++++++++++-------
 arch/x86/kvm/vmx/vmx.h                             |   9 +
 arch/x86/kvm/x86.c                                 | 197 ++++++++-----
 arch/x86/kvm/x86.h                                 |   2 +-
 include/linux/cpu.h                                |   2 +
 include/uapi/linux/kvm.h                           |   1 +
 kernel/cpu.c                                       |  11 +-
 kernel/locking/qspinlock_paravirt.h                |   2 +-
 tools/objtool/check.c                              |   1 -
 tools/testing/selftests/kvm/dirty_log_test.c       |  79 ++----
 tools/testing/selftests/kvm/include/kvm_util.h     |  18 +-
 .../selftests/kvm/include/x86_64/processor.h       |   3 +
 .../testing/selftests/kvm/lib/aarch64/processor.c  |   3 +
 tools/testing/selftests/kvm/lib/kvm_util.c         |  67 ++++-
 tools/testing/selftests/kvm/lib/x86_64/processor.c |  30 +-
 tools/testing/selftests/kvm/lib/x86_64/ucall.c     |   2 +-
 tools/testing/selftests/kvm/x86_64/hyperv_cpuid.c  |  27 ++
 36 files changed, 906 insertions(+), 468 deletions(-)
```
#### [PATCH v7 1/7] KVM: CPUID: Fix IA32_XSS support in CPUID(0xd,i) enumeration
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11163643
Return-Path: <SRS0=cTVl=XW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1AC0C112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Sep 2019 02:17:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id ECEBF217D7
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Sep 2019 02:17:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728230AbfI0CRM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 26 Sep 2019 22:17:12 -0400
Received: from mga17.intel.com ([192.55.52.151]:25572 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726140AbfI0CRL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 26 Sep 2019 22:17:11 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga003.jf.intel.com ([10.7.209.27])
  by fmsmga107.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 26 Sep 2019 19:17:10 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,553,1559545200";
   d="scan'208";a="193020643"
Received: from unknown (HELO local-michael-cet-test.sh.intel.com)
 ([10.239.159.128])
  by orsmga003.jf.intel.com with ESMTP; 26 Sep 2019 19:17:08 -0700
From: Yang Weijiang <weijiang.yang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        pbonzini@redhat.com, sean.j.christopherson@intel.com
Cc: mst@redhat.com, rkrcmar@redhat.com, jmattson@google.com,
        Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH v7 1/7] KVM: CPUID: Fix IA32_XSS support in CPUID(0xd,i)
 enumeration
Date: Fri, 27 Sep 2019 10:19:21 +0800
Message-Id: <20190927021927.23057-2-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
In-Reply-To: <20190927021927.23057-1-weijiang.yang@intel.com>
References: <20190927021927.23057-1-weijiang.yang@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The control bits in IA32_XSS MSR are being used for new features,
but current CPUID(0xd,i) enumeration code doesn't support them, so
fix existing code first.

The supervisor states in IA32_XSS haven't been used in public
KVM code, so set KVM_SUPPORTED_XSS to 0 now, anyone who's developing
IA32_XSS related feature may expand the macro to add the CPUID support,
otherwise, CPUID(0xd,i>1) always reports 0 of the subleaf to guest.

Extracted old code into a new filter and keep it same flavor as others.

This patch passed selftest on a few Intel platforms.

Suggested-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>
---
 arch/x86/include/asm/kvm_host.h |  1 +
 arch/x86/kvm/cpuid.c            | 94 +++++++++++++++++++++------------
 arch/x86/kvm/svm.c              |  7 +++
 arch/x86/kvm/vmx/vmx.c          |  6 +++
 arch/x86/kvm/x86.h              |  7 +++
 5 files changed, 82 insertions(+), 33 deletions(-)

```
#### [PATCH] KVM: Don't shrink/grow vCPU halt_poll_ns if host side polling is disabled
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11164061
Return-Path: <SRS0=cTVl=XW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4BFF4924
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Sep 2019 08:27:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 29CB12146E
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Sep 2019 08:27:13 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="l52EV2R5"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726404AbfI0I1J (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 27 Sep 2019 04:27:09 -0400
Received: from mail-pl1-f195.google.com ([209.85.214.195]:33283 "EHLO
        mail-pl1-f195.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725842AbfI0I1J (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 27 Sep 2019 04:27:09 -0400
Received: by mail-pl1-f195.google.com with SMTP id d22so796726pls.0;
        Fri, 27 Sep 2019 01:27:08 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=6FZld6NyLvsWL2o4u7zTXB1hPtoeXTwRo8zEqYJfiKE=;
        b=l52EV2R5p6/wbHuZ7Du1+8xPCkXqUWWl864aST5vKDXKUTBIqq3H8Ft+uF3hmPZSlP
         nswHPvtegQrcrpzU0b+0j0PTNrQtFPyXxSQYRZ2hqnKU81L4TkaiXkTH15wy17ggAKhG
         A9Fkf4n9pAijobJf5+L6tupEp0mALV9v2yP2A+/uX3fJqvtZogTOa8pudagklRN8GSOH
         dcmgS+bdUiaFitQDifUxzjJP5sgKvQPejcCLC+21NNg9bsqr5J6u0F/wqHn7/WitwGnC
         mzmwDK83aQUp8neoaimuZoaMmPIjQ86l5+6i7a29NkCT1fGXkFT/Igg61ldxv4FfFeed
         YXOg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=6FZld6NyLvsWL2o4u7zTXB1hPtoeXTwRo8zEqYJfiKE=;
        b=dDWiXhxs4zKIzSHAAM5r10l5H6XW+yy6nPMTuub4FPFCP4Z2PBxHmpTs//40HC0e0W
         sJL8jeZ2H8NqgBggT6njJTRsUfumBxoe6rL3GGmQ5MFDtnA7qRdGvpS1iyUZjvm3ZVGu
         DB4lptAgK03RDrR/AJD3kZetOTO5PpYg73ZIIXWqZ/QZbI/PsNOnwbBthuFZf+AnJdHk
         C6pEocIZ+6bPgY1fH6ir6X2O3WUr3wHJGnix/+JCrPWBBNq2PI06j0+7LDo7mYWNws6s
         4oX3RUtG6qAsRk53hnHdwdMGd16D9QTzdYC7nT8DRQnj33llhF9xYBk7NelUFSDCn36W
         iUbg==
X-Gm-Message-State: APjAAAVukFWyOUwrU0B+dfGyFgwAavi9Y59xLaKZijEJAbpIBaKpwxIe
        aHivzULd2OqKGnkdVSvzzC6kBJbd
X-Google-Smtp-Source: 
 APXvYqwzQglXoBTLIXgWxvQEeHnO8e7mA5or1UPjqdtSwLWyYE0B3CH2DugF5ttzoumQoESutBZ4Fw==
X-Received: by 2002:a17:902:d201:: with SMTP id
 t1mr3117240ply.337.1569572828338;
        Fri, 27 Sep 2019 01:27:08 -0700 (PDT)
Received: from localhost.localdomain ([203.205.141.123])
        by smtp.googlemail.com with ESMTPSA id
 d24sm2168594pfn.86.2019.09.27.01.27.05
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-SHA bits=128/128);
        Fri, 27 Sep 2019 01:27:07 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Wanpeng Li <wanpengli@tencent.com>,
 Jim Mattson <jmattson@google.com>, Joerg Roedel <joro@8bytes.org>,
 Marcelo Tosatti <mtosatti@redhat.com>
Subject: [PATCH] KVM: Don't shrink/grow vCPU halt_poll_ns if host side polling
 is disabled
Date: Fri, 27 Sep 2019 16:27:02 +0800
Message-Id: <1569572822-28942-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

Don't waste cycles to shrink/grow vCPU halt_poll_ns if host 
side polling is disabled.

Cc: Marcelo Tosatti <mtosatti@redhat.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 virt/kvm/kvm_main.c | 28 +++++++++++++++-------------
 1 file changed, 15 insertions(+), 13 deletions(-)

```
#### [PATCH v2 1/3] KVM: x86: assign two bits to track SPTE kinds
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11164359
Return-Path: <SRS0=cTVl=XW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 789CD14E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Sep 2019 11:16:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5510B2146E
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Sep 2019 11:16:03 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="tghHbK7Z"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727079AbfI0LPv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 27 Sep 2019 07:15:51 -0400
Received: from mail-wm1-f66.google.com ([209.85.128.66]:39851 "EHLO
        mail-wm1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726203AbfI0LPu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 27 Sep 2019 07:15:50 -0400
Received: by mail-wm1-f66.google.com with SMTP id v17so5742718wml.4;
        Fri, 27 Sep 2019 04:15:48 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=t6GKWk10SkA1KjsImI2OSEARlm/dqk+IOcuAz8AZeOE=;
        b=tghHbK7ZlAi5aohh+D6j7HzrMUogf1wWotzAml6VuA4i9EAjAAQ55hHA7/Dl2FIgg0
         ZhON54m0TcXUq8SPEaqBvVKM+RQ2CbkqVWOfxrIkFwx/tJlOWlw9Jk5eccbwESbjo7We
         FoNYP5P+WPk0YD3XQEcnU1T5UHFuIzk2mAJAAJ0uXVEqwT4bExE9bcR8kyubuMIrbFNJ
         irWj6D3nOGdLb4sdownRAT9EQi0bdrFS1vtrF+dMTZRSYq+OJxhwKj1hg7bQ+Kz2wpuf
         7a4i7UdXFPJ/fBYlOicF0aoMUZ/zdp4+GQ95kxJQ78GoC7PLcko0z8OEGQPSwIq6pItt
         JHLQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :in-reply-to:references;
        bh=t6GKWk10SkA1KjsImI2OSEARlm/dqk+IOcuAz8AZeOE=;
        b=Ktc+jvKXzmf1kyZbWB+T29APMyTfV7O0Ud7NumcycCTZovOfE7FLLbByC4c/cB2FDE
         402hY8IWkxWB+quixXi5i0WkJxt5E+KeYAfYM8TutAu5AV84Y/pQkQAegLCOD76xy7wr
         17At8jQZwXr0YkK2uXRF6tLnqoOln7FrX6g6Dh0hcX8E36T/Rbk48wFxsRdApBKPbDBp
         ywWv4F8hYblhyaEI7Yyu/DtHICNqi8V0Q5yJDaamFnjfZGKYwP9hjoZx+EhahALeTJV3
         hgiT4Cf/ZDhS6LR9MzxZlEo/p3yT95mHYIL9+oTK64Go7BULZk+6vAC78aP5VLqVVRkn
         5WJQ==
X-Gm-Message-State: APjAAAWXZTPG4j0VFokgBw3ly0TlO2g1rVnwOouO5SaOpE/RnS0vp5+E
        cPC0Wm/3vCq4LZo7kqQpYfsesT5m
X-Google-Smtp-Source: 
 APXvYqyOz9S1L/GzjXdgBlPZ9lojqo+smdIw+YQ1V+kd+iv9rYPfAso3DfSR9G73ARTCviuhr0BzIg==
X-Received: by 2002:a7b:c0d4:: with SMTP id s20mr7045183wmh.101.1569582947506;
        Fri, 27 Sep 2019 04:15:47 -0700 (PDT)
Received: from 640k.lan ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 r28sm2913848wrr.94.2019.09.27.04.15.46
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Fri, 27 Sep 2019 04:15:46 -0700 (PDT)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Junaid Shahid <junaids@google.com>
Subject: [PATCH v2 1/3] KVM: x86: assign two bits to track SPTE kinds
Date: Fri, 27 Sep 2019 13:15:41 +0200
Message-Id: <1569582943-13476-2-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1569582943-13476-1-git-send-email-pbonzini@redhat.com>
References: <1569582943-13476-1-git-send-email-pbonzini@redhat.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Currently, we are overloading SPTE_SPECIAL_MASK to mean both
"A/D bits unavailable" and MMIO, where the difference between the
two is determined by mio_mask and mmio_value.

However, the next patch will need two bits to distinguish
availability of A/D bits from write protection.  So, while at
it give MMIO its own bit pattern, and move the two bits from
bit 62 to bits 52..53 since Intel is allocating EPT page table
bits from the top.

Reviewed-by: Junaid Shahid <junaids@google.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/include/asm/kvm_host.h |  7 -------
 arch/x86/kvm/mmu.c              | 28 ++++++++++++++++++----------
 2 files changed, 18 insertions(+), 17 deletions(-)

```
#### [PATCH v2 1/6] KVM: PPC: Book3S HV: XIVE: Set kvm->arch.xive when VPs are allocated
##### From: Greg Kurz <groug@kaod.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Greg Kurz <groug@kaod.org>
X-Patchwork-Id: 11164415
Return-Path: <SRS0=cTVl=XW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DE68E13BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Sep 2019 11:53:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C6B0021850
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Sep 2019 11:53:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727262AbfI0Lxr (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 27 Sep 2019 07:53:47 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:56592 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726843AbfI0Lxr (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 27 Sep 2019 07:53:47 -0400
Received: from pps.filterd (m0098396.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x8RBkp0B077724
        for <kvm@vger.kernel.org>; Fri, 27 Sep 2019 07:53:46 -0400
Received: from e06smtp01.uk.ibm.com (e06smtp01.uk.ibm.com [195.75.94.97])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2v9ft8vnh0-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Fri, 27 Sep 2019 07:53:46 -0400
Received: from localhost
        by e06smtp01.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <groug@kaod.org>;
        Fri, 27 Sep 2019 12:53:44 +0100
Received: from b06cxnps4074.portsmouth.uk.ibm.com (9.149.109.196)
        by e06smtp01.uk.ibm.com (192.168.101.131) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Fri, 27 Sep 2019 12:53:39 +0100
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x8RBrcum42008656
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 27 Sep 2019 11:53:38 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id C77C0A4060;
        Fri, 27 Sep 2019 11:53:38 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 636E5A405C;
        Fri, 27 Sep 2019 11:53:38 +0000 (GMT)
Received: from bahia.lan (unknown [9.145.172.9])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 27 Sep 2019 11:53:38 +0000 (GMT)
Subject: [PATCH v2 1/6] KVM: PPC: Book3S HV: XIVE: Set kvm->arch.xive when
 VPs are allocated
From: Greg Kurz <groug@kaod.org>
To: Paul Mackerras <paulus@ozlabs.org>
Cc: Michael Ellerman <mpe@ellerman.id.au>,
 Benjamin Herrenschmidt <benh@kernel.crashing.org>,
 =?utf-8?q?C=C3=A9dric?= Le Goater <clg@kaod.org>,
 David Gibson <david@gibson.dropbear.id.au>,
 Paolo Bonzini <pbonzini@redhat.com>,
 Radim =?utf-8?b?S3LEjW3DocWZ?= <rkrcmar@redhat.com>, kvm-ppc@vger.kernel.org,
 kvm@vger.kernel.org, linuxppc-dev@lists.ozlabs.org, stable@vger.kernel.org
Date: Fri, 27 Sep 2019 13:53:38 +0200
In-Reply-To: <156958521220.1503771.2119482814236775333.stgit@bahia.lan>
References: <156958521220.1503771.2119482814236775333.stgit@bahia.lan>
User-Agent: StGit/unknown-version
MIME-Version: 1.0
Content-Type: text/plain; charset="utf-8"
X-TM-AS-GCONF: 00
x-cbid: 19092711-4275-0000-0000-0000036BC508
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19092711-4276-0000-0000-0000387E46FB
Message-Id: <156958521804.1503771.3961610486487789036.stgit@bahia.lan>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-09-27_06:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=0 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1034 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=999 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1908290000 definitions=main-1909270112
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If we cannot allocate the XIVE VPs in OPAL, the creation of a XIVE or
XICS-on-XIVE device is aborted as expected, but we leave kvm->arch.xive
set forever since the release method isn't called in this case. Any
subsequent tentative to create a XIVE or XICS-on-XIVE for this VM will
thus always fail (DoS). This is a problem for QEMU since it destroys
and re-creates these devices when the VM is reset: the VM would be
restricted to using the much slower emulated XIVE or XICS forever.

As an alternative to adding rollback, do not assign kvm->arch.xive before
making sure the XIVE VPs are allocated in OPAL.

Cc: stable@vger.kernel.org # v5.2
Fixes: 5422e95103cf ("KVM: PPC: Book3S HV: XIVE: Replace the 'destroy' method by a 'release' method")
Signed-off-by: Greg Kurz <groug@kaod.org>
Reviewed-by: Cédric Le Goater <clg@kaod.org>
---
 arch/powerpc/kvm/book3s_xive.c        |   11 +++++------
 arch/powerpc/kvm/book3s_xive_native.c |    2 +-
 2 files changed, 6 insertions(+), 7 deletions(-)

```
#### [PATCH] KVM: selftests: x86: clarify what is reported on KVM_GET_MSRS failure
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11164767
Return-Path: <SRS0=cTVl=XW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D97BA1599
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Sep 2019 15:54:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C22E821841
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Sep 2019 15:54:32 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727355AbfI0Py3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 27 Sep 2019 11:54:29 -0400
Received: from mx1.redhat.com ([209.132.183.28]:52708 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726251AbfI0Py3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 27 Sep 2019 11:54:29 -0400
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id E2976306059B;
        Fri, 27 Sep 2019 15:54:28 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.205.253])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 115416293B;
        Fri, 27 Sep 2019 15:54:14 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>,
	=?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Jim Mattson <jmattson@google.com>
Subject: [PATCH] KVM: selftests: x86: clarify what is reported on KVM_GET_MSRS
 failure
Date: Fri, 27 Sep 2019 17:54:13 +0200
Message-Id: <20190927155413.31648-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.46]);
 Fri, 27 Sep 2019 15:54:28 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When KVM_GET_MSRS fail the report looks like

==== Test Assertion Failure ====
  lib/x86_64/processor.c:1089: r == nmsrs
  pid=28775 tid=28775 - Argument list too long
     1	0x000000000040a55f: vcpu_save_state at processor.c:1088 (discriminator 3)
     2	0x00000000004010e3: main at state_test.c:171 (discriminator 4)
     3	0x00007fb8e69223d4: ?? ??:0
     4	0x0000000000401287: _start at ??:?
  Unexpected result from KVM_GET_MSRS, r: 36 (failed at 194)

and it's not obvious that '194' here is the failed MSR index and that
it's printed in hex. Change that.

Suggested-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 tools/testing/selftests/kvm/lib/x86_64/processor.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2 1/8] KVM: nVMX: Always write vmcs02.GUEST_CR3 during nested VM-Enter
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11165185
Return-Path: <SRS0=cTVl=XW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 916291709
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Sep 2019 21:46:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 778D120863
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Sep 2019 21:46:04 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728442AbfI0VqA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 27 Sep 2019 17:46:00 -0400
Received: from mga12.intel.com ([192.55.52.136]:45951 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728077AbfI0VpZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 27 Sep 2019 17:45:25 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga003.fm.intel.com ([10.253.24.29])
  by fmsmga106.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 27 Sep 2019 14:45:25 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,557,1559545200";
   d="scan'208";a="196852057"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.41])
  by FMSMGA003.fm.intel.com with ESMTP; 27 Sep 2019 14:45:24 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Reto Buerki <reet@codelabs.ch>,
        Liran Alon <liran.alon@oracle.com>
Subject: [PATCH v2 1/8] KVM: nVMX: Always write vmcs02.GUEST_CR3 during nested
 VM-Enter
Date: Fri, 27 Sep 2019 14:45:16 -0700
Message-Id: <20190927214523.3376-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.22.0
In-Reply-To: <20190927214523.3376-1-sean.j.christopherson@intel.com>
References: <20190927214523.3376-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Write the desired L2 CR3 into vmcs02.GUEST_CR3 during nested VM-Enter
instead of deferring the VMWRITE until vmx_set_cr3().  If the VMWRITE
is deferred, then KVM can consume a stale vmcs02.GUEST_CR3 when it
refreshes vmcs12->guest_cr3 during nested_vmx_vmexit() if the emulated
VM-Exit occurs without actually entering L2, e.g. if the nested run
is squashed because nested VM-Enter (from L1) is putting L2 into HLT.

Note, the above scenario can occur regardless of whether L1 is
intercepting HLT, e.g. L1 can intercept HLT and then re-enter L2 with
vmcs.GUEST_ACTIVITY_STATE=HALTED.  But practically speaking, a VMM will
likely put a guest into HALTED if and only if it's not intercepting HLT.

In an ideal world where EPT *requires* unrestricted guest (and vice
versa), VMX could handle CR3 similar to how it handles RSP and RIP,
e.g. mark CR3 dirty and conditionally load it at vmx_vcpu_run().  But
the unrestricted guest silliness complicates the dirty tracking logic
to the point that explicitly handling vmcs02.GUEST_CR3 during nested
VM-Enter is a simpler overall implementation.

Cc: stable@vger.kernel.org
Reported-and-tested-by: Reto Buerki <reet@codelabs.ch>
Tested-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/nested.c | 10 ++++++++++
 arch/x86/kvm/vmx/vmx.c    | 10 +++++++---
 2 files changed, 17 insertions(+), 3 deletions(-)

```
#### [PATCH v2] KVM: VMX: Set VMENTER_L1D_FLUSH_NOT_REQUIRED if !X86_BUG_L1TF
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11164779
Return-Path: <SRS0=cTVl=XW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7F96676
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Sep 2019 16:05:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5E2EB21850
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Sep 2019 16:05:25 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="tWZt3K4l"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727887AbfI0QFV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 27 Sep 2019 12:05:21 -0400
Received: from mail-wr1-f66.google.com ([209.85.221.66]:39519 "EHLO
        mail-wr1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727624AbfI0QFV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 27 Sep 2019 12:05:21 -0400
Received: by mail-wr1-f66.google.com with SMTP id r3so3701086wrj.6;
        Fri, 27 Sep 2019 09:05:19 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=gMGe1RxHLB7ktDM+P7ngRhIvwgy8WL2hbGJxbnP4AYg=;
        b=tWZt3K4lxY9TyOFlfpmgYUURbaM2YtjqW2Tn6Qn9UB4suAdWVtz6rimKk/o2y17zIc
         0D5Qq/LdkLObm/VAKzJFQSREpzD1ZdvWMom+0Jp3J0Sc7vxs/aq1a3S927C7GEVFROyY
         OVolY6iVD3VCMYPzsN9RWpYGngxOl+RwW9j2jNI+yD/WGjhvUquuV5XSnM9QpPQ7qUOT
         fBOIqw+YKVU69QzT+shWplvB24c7rOnchBpey6wqPw6HOmhDkCVnZChWz/OSQT/ltx9X
         OY2RylsKsAuipYpV5ONedCVY4UejzzrDb+f9bJdjZmRWc1VE1Ppk4HKLm1rCPgfgDkh8
         tRXw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=gMGe1RxHLB7ktDM+P7ngRhIvwgy8WL2hbGJxbnP4AYg=;
        b=ibo1x4LSAnXGxp+gP5e+7zYYFqHLJgR/zteQz9HtCpiwOWYiI1dkZ8/9KwqiVxuMRT
         dNYu85P0hWwxz1B1Y8TxB16LWA33SUavqIRwGXwft6OEL8kY0bhclz0fL30WbyF3HuNQ
         TVgKfipriC7d/5yPgnpAWtP5v2oj5Mvv0xJNzjdl2dzMgmAlvPD/6uZTuMbklt+6JLL+
         VUDZkUh2PlXZRlH3p1xs1K9g+1WgzjU/1iFIpH9JSPWQqdREA+bIU2x615WUovmQWk4J
         kbWKCPirq/7iG1/Qvu3sbGyhZrI8agHmCqLLTCrtpPcF3iWSZVPeVLty/v5X8xWX0glR
         Shtw==
X-Gm-Message-State: APjAAAWJQiwcdbzN5HWJMNf3g0FltA1vGyMsa12qEanQ0N6yx+4r3zm/
        46B0AOlHIWt8ar5FGQaMRRmbTvWp
X-Google-Smtp-Source: 
 APXvYqzrf/BNCHYjyJATAYJdCzH3MpkGG2RZJC595mLoHIWxWvFh0FaUQydvQV/sCeYQrDbgNwgCyQ==
X-Received: by 2002:adf:ce89:: with SMTP id r9mr685277wrn.335.1569600318893;
        Fri, 27 Sep 2019 09:05:18 -0700 (PDT)
Received: from 640k.lan ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 g24sm3475615wrb.35.2019.09.27.09.05.17
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Fri, 27 Sep 2019 09:05:17 -0700 (PDT)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: bp@alien8.de, Waiman Long <longman@redhat.com>
Subject: [PATCH v2] KVM: VMX: Set VMENTER_L1D_FLUSH_NOT_REQUIRED if
 !X86_BUG_L1TF
Date: Fri, 27 Sep 2019 18:05:16 +0200
Message-Id: <1569600316-35966-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Waiman Long <longman@redhat.com>

The l1tf_vmx_mitigation is only set to VMENTER_L1D_FLUSH_NOT_REQUIRED
when the ARCH_CAPABILITIES MSR indicates that L1D flush is not required.
However, if the CPU is not affected by L1TF, l1tf_vmx_mitigation will
still be set to VMENTER_L1D_FLUSH_AUTO. This is certainly not the best
option for a !X86_BUG_L1TF CPU.

So force l1tf_vmx_mitigation to VMENTER_L1D_FLUSH_NOT_REQUIRED to make it
more explicit in case users are checking the vmentry_l1d_flush parameter.

Signed-off-by: Waiman Long <longman@redhat.com>
[Patch rewritten accoring to Borislav Petkov's suggestion. - Paolo]
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/vmx/vmx.c | 15 +++++++++------
 1 file changed, 9 insertions(+), 6 deletions(-)

```
#### [PATCH v2] vsock/virtio: add support for MSG_PEEK
##### From: Matias Ezequiel Vara Larsen <matiasevara@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Matias Ezequiel Vara Larsen <matiasevara@gmail.com>
X-Patchwork-Id: 11164849
Return-Path: <SRS0=cTVl=XW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 88CA4112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Sep 2019 16:45:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 67118207E0
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Sep 2019 16:45:15 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="RcW3JOWX"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727836AbfI0QpL (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 27 Sep 2019 12:45:11 -0400
Received: from mail-wr1-f66.google.com ([209.85.221.66]:39125 "EHLO
        mail-wr1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726251AbfI0QpK (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 27 Sep 2019 12:45:10 -0400
Received: by mail-wr1-f66.google.com with SMTP id r3so3942678wrj.6;
        Fri, 27 Sep 2019 09:45:07 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=og90qbQAXOicdq5w4qtLw6dYo5vnyUk8y6wc3hp/goU=;
        b=RcW3JOWX3CaxFUDNoQDHbdGdVcFVnBOj7k7rc3z1VvB6lT5ldwqAICaj7FIaWmmLBa
         E3822z+bFuwc702xgCM2HYqCKR9wEOFKHpYR/ZP6ZTdL2lvmPnI6k3K9hvJQgeRY5yTC
         yMA5u4+AINc1hPUvJkP6yjv18x6r1XpxWZsXDcsqcGsGVCWWGTGlWudM0Ti6KMQoXvQf
         gL6MmMMALNqvxqz0Gg5Uq0k7NSNR+drcdLv5LJSN5eVRCkmMN0XiKC29r7quWU2erzOe
         xfNdMTKgKJs89lS7tv4BTRQhubJS/UTaAzzDX+mXoZc7ZTyvy8uqF98Zryq8oEGAWHgN
         cVwQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references;
        bh=og90qbQAXOicdq5w4qtLw6dYo5vnyUk8y6wc3hp/goU=;
        b=j2PElocYRW0Krd2xB3KV5FYDdDbGWQwsjohA8ivRvoxQ+yggRVCPJofldnYnErNlKp
         szWWV0UaFt3xyUTnJAaV/jJiEy/Vk7cpGGKnn58qn9wIxYoo+LeOdD1hgqEvz3G+2LOf
         V692jqoG6hu6c9gVKLwsr9ijI5mYazEeqs0XMmoVhjuauK00Fo5gW3/pn3kCAOhlN88F
         QiFXuXoPYfAM9igXfAr88Q6pV1vSWgfTYWm346tDJcmIbNmLmPXb1rBwBa38+jCZBl8V
         K1O1nRgD1qk5fAkQqBxnL5dRZ8d1H4nEPDjN3KDSshvG5I0LuHesz6zvwxmE3MTVSh4L
         5Bcg==
X-Gm-Message-State: APjAAAUot2x48quyhH/cfrtu7oVLcd3Rl/VLfaEhT2kg19fnM/EuEVyZ
        kEwigqDMOTHsAnqHlqZKxLk=
X-Google-Smtp-Source: 
 APXvYqzB8omaq85cbWYuSm9buXKmXpapBFdkbhwBVUoZfj9O4XopENPYw/IDgrNoGyrxG2qggAUQdQ==
X-Received: by 2002:a1c:cb05:: with SMTP id b5mr7750360wmg.79.1569602706717;
        Fri, 27 Sep 2019 09:45:06 -0700 (PDT)
Received: from scw-93ddc8.cloud.online.net ([2001:bc8:4400:2400::302d])
        by smtp.googlemail.com with ESMTPSA id
 h125sm11889243wmf.31.2019.09.27.09.45.05
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-SHA bits=128/128);
        Fri, 27 Sep 2019 09:45:05 -0700 (PDT)
From: Matias Ezequiel Vara Larsen <matiasevara@gmail.com>
To: stefanha@redhat.com
Cc: davem@davemloft.net, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        linux-kernel@vger.kernel.org, matiasevara@gmail.com,
        sgarzare@redhat.com, eric.dumazet@gmail.com
Subject: [PATCH v2] vsock/virtio: add support for MSG_PEEK
Date: Fri, 27 Sep 2019 16:44:23 +0000
Message-Id: <1569602663-16815-1-git-send-email-matiasevara@gmail.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1569522214-28223-1-git-send-email-matiasevara@gmail.com>
References: <1569522214-28223-1-git-send-email-matiasevara@gmail.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch adds support for MSG_PEEK. In such a case, packets are not
removed from the rx_queue and credit updates are not sent.

Signed-off-by: Matias Ezequiel Vara Larsen <matiasevara@gmail.com>
---
 net/vmw_vsock/virtio_transport_common.c | 55 +++++++++++++++++++++++++++++++--
 1 file changed, 52 insertions(+), 3 deletions(-)

```
#### [PATCH v9] KVM: vmx: Introduce handle_unexpected_vmexit and handle WAITPKG vmexit
##### From: Tao Xu <tao3.xu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tao Xu <tao3.xu@intel.com>
X-Patchwork-Id: 11164031
Return-Path: <SRS0=cTVl=XW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BB61B1747
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Sep 2019 07:46:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A46F9207FF
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Sep 2019 07:46:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726440AbfI0HqW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 27 Sep 2019 03:46:22 -0400
Received: from mga01.intel.com ([192.55.52.88]:59042 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726385AbfI0HqW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 27 Sep 2019 03:46:22 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by fmsmga101.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 27 Sep 2019 00:46:21 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,554,1559545200";
   d="scan'208";a="201935622"
Received: from tao-optiplex-7060.sh.intel.com ([10.239.159.36])
  by orsmga002.jf.intel.com with ESMTP; 27 Sep 2019 00:46:19 -0700
From: Tao Xu <tao3.xu@intel.com>
To: kvm@vger.kernel.org, liran.alon@oracle.com, pbonzini@redhat.com,
        sean.j.christopherson@intel.com
Cc: Tao Xu <tao3.xu@intel.com>, Jingqi Liu <jingqi.liu@intel.com>
Subject: [PATCH v9] KVM: vmx: Introduce handle_unexpected_vmexit and handle
 WAITPKG vmexit
Date: Fri, 27 Sep 2019 15:46:16 +0800
Message-Id: <20190927074616.31092-1-tao3.xu@intel.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

As the latest Intel 64 and IA-32 Architectures Software Developer's
Manual, UMWAIT and TPAUSE instructions cause a VM exit if the
RDTSC exiting and enable user wait and pause VM-execution
controls are both 1.

Because KVM never enable RDTSC exiting, the vm-exit for UMWAIT and
TPAUSE should never happen. Considering EXIT_REASON_XSAVES and
EXIT_REASON_XRSTORS is also unexpected VM-exit for KVM. Reuse the code
of 'commit 7396d337cfad ("KVM: x86: Return to userspace with internal
error on unexpected exit reason"), and introduce a common exit helper
handle_unexpected_vmexit() to handle these unexpected VM-exit.

Suggested-by: Sean Christopherson <sean.j.christopherson@intel.com>
Co-developed-by: Jingqi Liu <jingqi.liu@intel.com>
Signed-off-by: Jingqi Liu <jingqi.liu@intel.com>
Signed-off-by: Tao Xu <tao3.xu@intel.com>
---
 arch/x86/include/uapi/asm/vmx.h |  6 +++-
 arch/x86/kvm/vmx/nested.c       |  4 +++
 arch/x86/kvm/vmx/vmx.c          | 51 ++++++++++++++++-----------------
 3 files changed, 33 insertions(+), 28 deletions(-)

```
#### [RFC PATCH 01/13] vsock/vmci: remove unused VSOCK_DEFAULT_CONNECT_TIMEOUT
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefano Garzarella <sgarzare@redhat.com>
X-Patchwork-Id: 11164365
Return-Path: <SRS0=cTVl=XW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 39F6D76
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Sep 2019 11:27:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 17AAD217D9
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Sep 2019 11:27:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727205AbfI0L1X (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 27 Sep 2019 07:27:23 -0400
Received: from mx1.redhat.com ([209.132.183.28]:39806 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725890AbfI0L1W (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 27 Sep 2019 07:27:22 -0400
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id BD24A8A1CA7;
        Fri, 27 Sep 2019 11:27:21 +0000 (UTC)
Received: from steredhat.redhat.com (ovpn-117-249.ams2.redhat.com
 [10.36.117.249])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 3F2445D9C3;
        Fri, 27 Sep 2019 11:27:17 +0000 (UTC)
From: Stefano Garzarella <sgarzare@redhat.com>
To: netdev@vger.kernel.org
Cc: linux-hyperv@vger.kernel.org,
        "K. Y. Srinivasan" <kys@microsoft.com>,
        Stefan Hajnoczi <stefanha@redhat.com>,
        Sasha Levin <sashal@kernel.org>, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, "David S. Miller" <davem@davemloft.net>,
        virtualization@lists.linux-foundation.org,
        Stephen Hemminger <sthemmin@microsoft.com>,
        Jason Wang <jasowang@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Haiyang Zhang <haiyangz@microsoft.com>,
        Dexuan Cui <decui@microsoft.com>,
        Jorgen Hansen <jhansen@vmware.com>
Subject: [RFC PATCH 01/13] vsock/vmci: remove unused
 VSOCK_DEFAULT_CONNECT_TIMEOUT
Date: Fri, 27 Sep 2019 13:26:51 +0200
Message-Id: <20190927112703.17745-2-sgarzare@redhat.com>
In-Reply-To: <20190927112703.17745-1-sgarzare@redhat.com>
References: <20190927112703.17745-1-sgarzare@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.6.2 (mx1.redhat.com [10.5.110.69]);
 Fri, 27 Sep 2019 11:27:21 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The VSOCK_DEFAULT_CONNECT_TIMEOUT definition was introduced with
commit d021c344051af ("VSOCK: Introduce VM Sockets"), but it is
never used in the net/vmw_vsock/vmci_transport.c.

VSOCK_DEFAULT_CONNECT_TIMEOUT is used and defined in
net/vmw_vsock/af_vsock.c

Signed-off-by: Stefano Garzarella <sgarzare@redhat.com>
---
 net/vmw_vsock/vmci_transport.c | 5 -----
 1 file changed, 5 deletions(-)

```
