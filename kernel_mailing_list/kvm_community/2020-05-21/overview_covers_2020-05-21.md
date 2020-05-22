

#### [RFC v2 00/18] Refactor configuration of guest memory protection
##### From: David Gibson <david@gibson.dropbear.id.au>

```c
From patchwork Thu May 21 03:42:46 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Gibson <david@gibson.dropbear.id.au>
X-Patchwork-Id: 11562159
Return-Path: <SRS0=9zq6=7D=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4FB2A159A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 21 May 2020 03:43:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 37E53207C4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 21 May 2020 03:43:15 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=gibson.dropbear.id.au
 header.i=@gibson.dropbear.id.au header.b="qJ8yxNE6"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728184AbgEUDnO (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 20 May 2020 23:43:14 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:39154 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728176AbgEUDnO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 20 May 2020 23:43:14 -0400
Received: from ozlabs.org (ozlabs.org [IPv6:2401:3900:2:1::2])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id E4F2CC061A0E
        for <kvm@vger.kernel.org>; Wed, 20 May 2020 20:43:13 -0700 (PDT)
Received: by ozlabs.org (Postfix, from userid 1007)
        id 49SFnr2hwtz9sT8; Thu, 21 May 2020 13:43:12 +1000 (AEST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple;
        d=gibson.dropbear.id.au; s=201602; t=1590032592;
        bh=JOC3I9CAO1gQokfZDDYIv1xerDCdFlfSPYuz9CpkVxs=;
        h=From:To:Cc:Subject:Date:From;
        b=qJ8yxNE6f8YCYFwiyEHO0m+5ZcldYuz3Yy6SWwKSMVH/7lYKGxCFkdPpd5Vjt5sQf
         iV4zdJmIgzgl7zVJcVNRlRD6uR0UOaljqzbJUXitmnUdEGEKnY3/3e/7WeC1wajSom
         Tj6pDUL/3gxd/QqPZUQcug5qXVBPTgNBrTAn7gDQ=
From: David Gibson <david@gibson.dropbear.id.au>
To: qemu-devel@nongnu.org, brijesh.singh@amd.com,
        frankja@linux.ibm.com, dgilbert@redhat.com, pair@us.ibm.com
Cc: qemu-ppc@nongnu.org, kvm@vger.kernel.org,
        David Gibson <david@gibson.dropbear.id.au>,
        mdroth@linux.vnet.ibm.com, cohuck@redhat.com,
        Marcel Apfelbaum <marcel.apfelbaum@gmail.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Richard Henderson <rth@twiddle.net>,
        Eduardo Habkost <ehabkost@redhat.com>
Subject: [RFC v2 00/18] Refactor configuration of guest memory protection
Date: Thu, 21 May 2020 13:42:46 +1000
Message-Id: <20200521034304.340040-1-david@gibson.dropbear.id.au>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

A number of hardware platforms are implementing mechanisms whereby the
hypervisor does not have unfettered access to guest memory, in order
to mitigate the security impact of a compromised hypervisor.

AMD's SEV implements this with in-cpu memory encryption, and Intel has
its own memory encryption mechanism.  POWER has an upcoming mechanism
to accomplish this in a different way, using a new memory protection
level plus a small trusted ultravisor.  s390 also has a protected
execution environment.

The current code (committed or draft) for these features has each
platform's version configured entirely differently.  That doesn't seem
ideal for users, or particularly for management layers.

AMD SEV introduces a notionally generic machine option
"machine-encryption", but it doesn't actually cover any cases other
than SEV.

This series is a proposal to at least partially unify configuration
for these mechanisms, by renaming and generalizing AMD's
"memory-encryption" property.  It is replaced by a
"guest-memory-protection" property pointing to a platform specific
object which configures and manages the specific details.

For now this series covers just AMD SEV and POWER PEF.  I'm hoping it
can be extended to cover the Intel and s390 mechanisms as well,
though.

Note: I'm using the term "guest memory protection" throughout to refer
to mechanisms like this.  I don't particular like the term, it's both
long and not really precise.  If someone can think of a succinct way
of saying "a means of protecting guest memory from a possibly
compromised hypervisor", I'd be grateful for the suggestion.

Changes since v1:
 * Rebased
 * Fixed some errors pointed out by Dave Gilbert

David Gibson (18):
  target/i386: sev: Remove unused QSevGuestInfoClass
  target/i386: sev: Move local structure definitions into .c file
  target/i386: sev: Rename QSevGuestInfo
  target/i386: sev: Embed SEVState in SevGuestState
  target/i386: sev: Partial cleanup to sev_state global
  target/i386: sev: Remove redundant cbitpos and reduced_phys_bits
    fields
  target/i386: sev: Remove redundant policy field
  target/i386: sev: Remove redundant handle field
  target/i386: sev: Unify SEVState and SevGuestState
  guest memory protection: Add guest memory protection interface
  guest memory protection: Handle memory encrption via interface
  guest memory protection: Perform KVM init via interface
  guest memory protection: Move side effect out of
    machine_set_memory_encryption()
  guest memory protection: Rework the "memory-encryption" property
  guest memory protection: Decouple kvm_memcrypt_*() helpers from KVM
  guest memory protection: Add Error ** to
    GuestMemoryProtection::kvm_init
  spapr: Added PEF based guest memory protection
  guest memory protection: Alter virtio default properties for protected
    guests

 accel/kvm/kvm-all.c                    |  40 +--
 accel/kvm/sev-stub.c                   |   5 -
 accel/stubs/kvm-stub.c                 |  10 -
 backends/Makefile.objs                 |   2 +
 backends/guest-memory-protection.c     |  29 ++
 hw/core/machine.c                      |  61 ++++-
 hw/i386/pc_sysfw.c                     |   6 +-
 include/exec/guest-memory-protection.h |  77 ++++++
 include/hw/boards.h                    |   4 +-
 include/sysemu/kvm.h                   |  17 --
 include/sysemu/sev.h                   |   6 +-
 target/i386/sev.c                      | 351 +++++++++++++------------
 target/i386/sev_i386.h                 |  49 ----
 target/ppc/Makefile.objs               |   2 +-
 target/ppc/pef.c                       |  81 ++++++
 15 files changed, 441 insertions(+), 299 deletions(-)
 create mode 100644 backends/guest-memory-protection.c
 create mode 100644 include/exec/guest-memory-protection.h
 create mode 100644 target/ppc/pef.c
```
