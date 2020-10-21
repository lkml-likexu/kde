

#### [RFCv2 00/16] KVM protected memory extension
##### From: "Kirill A. Shutemov" <kirill@shutemov.name>
X-Google-Original-From: "Kirill A. Shutemov" <kirill.shutemov@linux.intel.com>

```c
From patchwork Tue Oct 20 06:18:43 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: "Kirill A. Shutemov" <kirill@shutemov.name>
X-Patchwork-Id: 11845811
Return-Path: <SRS0=07X0=D3=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-6.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=no autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2C603C433DF
	for <kvm@archiver.kernel.org>; Tue, 20 Oct 2020 06:21:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D06C4222C8
	for <kvm@archiver.kernel.org>; Tue, 20 Oct 2020 06:21:17 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=shutemov-name.20150623.gappssmtp.com
 header.i=@shutemov-name.20150623.gappssmtp.com header.b="sABcN5Qa"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2403856AbgJTGTK (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 20 Oct 2020 02:19:10 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:48550 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2403842AbgJTGTI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 20 Oct 2020 02:19:08 -0400
Received: from mail-lj1-x241.google.com (mail-lj1-x241.google.com
 [IPv6:2a00:1450:4864:20::241])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 1DE82C0613D4
        for <kvm@vger.kernel.org>; Mon, 19 Oct 2020 23:19:08 -0700 (PDT)
Received: by mail-lj1-x241.google.com with SMTP id x16so759738ljh.2
        for <kvm@vger.kernel.org>; Mon, 19 Oct 2020 23:19:08 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=shutemov-name.20150623.gappssmtp.com; s=20150623;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=qy46RuuwUMCzWmTgEIxdF1BOhdP6zI3q5PMnJgwpnBs=;
        b=sABcN5QaSsunVLaxJ0We8Xt8MrzQTVy5cBduLMsOp5iNL1UcuB13+0+21Uv9bIcvoW
         C9sJyR15fwUZxskw8/vZoTuZMJ2BhQf5J3XjITgH9nQ5bhe4LqP4smFh/6k6QULitN3P
         dr2Yfcdnhnu00CH4eYADmFfNT+9uBCSkFbxxlZH3hRFyPZgiuXt+us40SYDIaFyD8UGi
         ZVtgsSDpMW4fAMwjfE9kyFoeBwLnVGC5IPCj3uet1VY05L5n90LWT6iaMaZgBcxSjff1
         s+Hu+p6gN25kQFyZEVSrzrmkkmeIgT7VF68yfQQtWh2f9owWe0JrnJs4Am2Qhd6M0J4K
         GHlA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=qy46RuuwUMCzWmTgEIxdF1BOhdP6zI3q5PMnJgwpnBs=;
        b=U21PvHDJck3gPjsIQpAJzwe4Pv5Ut/dgDzzJ19QysMTTDJi6oaXxC2Kj02RjEHixUd
         vxjy+GOcuYVUQ/LatOq5o0mzV8kiU6Jd0tpXMtlu1ocwb3a+ggRh14GySadtLFjSBB9l
         K4l8i/v4grPpkVwklrtEzt8WkQBgYqxZaoH2twW7UCJeFrGUhlypDpajw2DquD/3sVl9
         NpDrBMkmcMJ4+7EZI6Ja4jH8p6Ao8X6cpAvmA7qDxS5Xvg46bU3adV/JDeeJ+IxEoOnz
         MrzNBZyLxGH2gL6mkTuiULGaebfPltNVZp3YY3P03BUgayGXkuCCQKnForXg2JUqJZj9
         hM4w==
X-Gm-Message-State: AOAM533ILdZccDqw1zFjz35+4JZ2qpiBz4JwAYIM3RiE4jLnYPPbdHu/
        2GOhLv58Q1sSt6qcoMLJc9x8vitfiFzQlw==
X-Google-Smtp-Source: 
 ABdhPJxjJIWrUWM9VHKfS1XrHymQKfZS16xX42izRFnmIzpYdrTg+8toB6yA/wBC4CCUmWziRM0ysQ==
X-Received: by 2002:a05:651c:205a:: with SMTP id
 t26mr450811ljo.260.1603174746431;
        Mon, 19 Oct 2020 23:19:06 -0700 (PDT)
Received: from box.localdomain ([86.57.175.117])
        by smtp.gmail.com with ESMTPSA id
 x4sm135508lfn.280.2020.10.19.23.19.04
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 19 Oct 2020 23:19:04 -0700 (PDT)
From: "Kirill A. Shutemov" <kirill@shutemov.name>
X-Google-Original-From: "Kirill A. Shutemov" <kirill.shutemov@linux.intel.com>
Received: by box.localdomain (Postfix, from userid 1000)
        id B1A2F102328; Tue, 20 Oct 2020 09:19:01 +0300 (+03)
To: Dave Hansen <dave.hansen@linux.intel.com>,
        Andy Lutomirski <luto@kernel.org>,
        Peter Zijlstra <peterz@infradead.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Cc: David Rientjes <rientjes@google.com>,
        Andrea Arcangeli <aarcange@redhat.com>,
        Kees Cook <keescook@chromium.org>,
        Will Drewry <wad@chromium.org>,
        "Edgecombe, Rick P" <rick.p.edgecombe@intel.com>,
        "Kleen, Andi" <andi.kleen@intel.com>,
        Liran Alon <liran.alon@oracle.com>,
        Mike Rapoport <rppt@kernel.org>, x86@kernel.org,
        kvm@vger.kernel.org, linux-mm@kvack.org,
        linux-kernel@vger.kernel.org,
        "Kirill A. Shutemov" <kirill.shutemov@linux.intel.com>
Subject: [RFCv2 00/16] KVM protected memory extension
Date: Tue, 20 Oct 2020 09:18:43 +0300
Message-Id: <20201020061859.18385-1-kirill.shutemov@linux.intel.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

== Background / Problem ==

There are a number of hardware features (MKTME, SEV) which protect guest
memory from some unauthorized host access. The patchset proposes a purely
software feature that mitigates some of the same host-side read-only
attacks.


== What does this set mitigate? ==

 - Host kernel ”accidental” access to guest data (think speculation)

 - Host kernel induced access to guest data (write(fd, &guest_data_ptr, len))

 - Host userspace access to guest data (compromised qemu)

 - Guest privilege escalation via compromised QEMU device emulation

== What does this set NOT mitigate? ==

 - Full host kernel compromise.  Kernel will just map the pages again.

 - Hardware attacks


The second RFC revision addresses /most/ of the feedback.

I still didn't found a good solution to reboot and kexec. Unprotect all
the memory on such operations defeat the goal of the feature. Clearing up
most of the memory before unprotecting what is required for reboot (or
kexec) is tedious and error-prone.
Maybe we should just declare them unsupported?

== Series Overview ==

The hardware features protect guest data by encrypting it and then
ensuring that only the right guest can decrypt it.  This has the
side-effect of making the kernel direct map and userspace mapping
(QEMU et al) useless.  But, this teaches us something very useful:
neither the kernel or userspace mappings are really necessary for normal
guest operations.

Instead of using encryption, this series simply unmaps the memory. One
advantage compared to allowing access to ciphertext is that it allows bad
accesses to be caught instead of simply reading garbage.

Protection from physical attacks needs to be provided by some other means.
On Intel platforms, (single-key) Total Memory Encryption (TME) provides
mitigation against physical attacks, such as DIMM interposers sniffing
memory bus traffic.

The patchset modifies both host and guest kernel. The guest OS must enable
the feature via hypercall and mark any memory range that has to be shared
with the host: DMA regions, bounce buffers, etc. SEV does this marking via a
bit in the guest’s page table while this approach uses a hypercall.

For removing the userspace mapping, use a trick similar to what NUMA
balancing does: convert memory that belongs to KVM memory slots to
PROT_NONE: all existing entries converted to PROT_NONE with mprotect() and
the newly faulted in pages get PROT_NONE from the updated vm_page_prot.
The new VMA flag -- VM_KVM_PROTECTED -- indicates that the pages in the
VMA must be treated in a special way in the GUP and fault paths. The flag
allows GUP to return the page even though it is mapped with PROT_NONE, but
only if the new GUP flag -- FOLL_KVM -- is specified. Any userspace access
to the memory would result in SIGBUS. Any GUP access without FOLL_KVM
would result in -EFAULT.

Removing userspace mapping of the guest memory from QEMU process can help
to address some guest privilege escalation attacks. Consider the case when
unprivileged guest user exploits bug in a QEMU device emulation to gain
access to data it cannot normally have access within the guest.

Any anonymous page faulted into the VM_KVM_PROTECTED VMA gets removed from
the direct mapping with kernel_map_pages(). Note that kernel_map_pages() only
flushes local TLB. I think it's a reasonable compromise between security and
perfromance.

Zapping the PTE would bring the page back to the direct mapping after clearing.
At least for now, we don't remove file-backed pages from the direct mapping.
File-backed pages could be accessed via read/write syscalls. It adds
complexity.

Occasionally, host kernel has to access guest memory that was not made
shared by the guest. For instance, it happens for instruction emulation.
Normally, it's done via copy_to/from_user() which would fail with -EFAULT
now. We introduced a new pair of helpers: copy_to/from_guest(). The new
helpers acquire the page via GUP, map it into kernel address space with
kmap_atomic()-style mechanism and only then copy the data.

For some instruction emulation copying is not good enough: cmpxchg
emulation has to have direct access to the guest memory. __kvm_map_gfn()
is modified to accommodate the case.

The patchset is on top of v5.9

Kirill A. Shutemov (16):
  x86/mm: Move force_dma_unencrypted() to common code
  x86/kvm: Introduce KVM memory protection feature
  x86/kvm: Make DMA pages shared
  x86/kvm: Use bounce buffers for KVM memory protection
  x86/kvm: Make VirtIO use DMA API in KVM guest
  x86/kvmclock: Share hvclock memory with the host
  x86/realmode: Share trampoline area if KVM memory protection enabled
  KVM: Use GUP instead of copy_from/to_user() to access guest memory
  KVM: mm: Introduce VM_KVM_PROTECTED
  KVM: x86: Use GUP for page walk instead of __get_user()
  KVM: Protected memory extension
  KVM: x86: Enabled protected memory extension
  KVM: Rework copy_to/from_guest() to avoid direct mapping
  KVM: Handle protected memory in __kvm_map_gfn()/__kvm_unmap_gfn()
  KVM: Unmap protected pages from direct mapping
  mm: Do not use zero page for VM_KVM_PROTECTED VMAs

 arch/powerpc/kvm/book3s_64_mmu_hv.c    |   2 +-
 arch/powerpc/kvm/book3s_64_mmu_radix.c |   2 +-
 arch/s390/include/asm/pgtable.h        |   2 +-
 arch/x86/Kconfig                       |  11 +-
 arch/x86/include/asm/cpufeatures.h     |   1 +
 arch/x86/include/asm/io.h              |   6 +-
 arch/x86/include/asm/kvm_para.h        |   5 +
 arch/x86/include/asm/pgtable_types.h   |   1 +
 arch/x86/include/uapi/asm/kvm_para.h   |   3 +-
 arch/x86/kernel/kvm.c                  |  20 +++
 arch/x86/kernel/kvmclock.c             |   2 +-
 arch/x86/kernel/pci-swiotlb.c          |   3 +-
 arch/x86/kvm/Kconfig                   |   1 +
 arch/x86/kvm/cpuid.c                   |   3 +-
 arch/x86/kvm/mmu/mmu.c                 |   6 +-
 arch/x86/kvm/mmu/paging_tmpl.h         |  10 +-
 arch/x86/kvm/x86.c                     |   9 +
 arch/x86/mm/Makefile                   |   2 +
 arch/x86/mm/ioremap.c                  |  16 +-
 arch/x86/mm/mem_encrypt.c              |  51 ------
 arch/x86/mm/mem_encrypt_common.c       |  62 +++++++
 arch/x86/mm/pat/set_memory.c           |   7 +
 arch/x86/realmode/init.c               |   7 +-
 drivers/virtio/virtio_ring.c           |   4 +
 include/linux/kvm_host.h               |  11 +-
 include/linux/kvm_types.h              |   1 +
 include/linux/mm.h                     |  21 ++-
 include/uapi/linux/kvm_para.h          |   5 +-
 mm/gup.c                               |  20 ++-
 mm/huge_memory.c                       |  31 +++-
 mm/ksm.c                               |   2 +
 mm/memory.c                            |  18 +-
 mm/mmap.c                              |   3 +
 mm/rmap.c                              |   4 +
 virt/kvm/Kconfig                       |   3 +
 virt/kvm/async_pf.c                    |   2 +-
 virt/kvm/kvm_main.c                    | 238 +++++++++++++++++++++----
 virt/lib/Makefile                      |   1 +
 virt/lib/mem_protected.c               | 193 ++++++++++++++++++++
 39 files changed, 666 insertions(+), 123 deletions(-)
 create mode 100644 arch/x86/mm/mem_encrypt_common.c
 create mode 100644 virt/lib/mem_protected.c
```
#### [PATCH 0/2] KVM: Introduce ioeventfd read support
##### From: Amey Narkhede <ameynarkhede03@gmail.com>

```c
From patchwork Tue Oct 20 17:00:54 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Amey Narkhede <ameynarkhede03@gmail.com>
X-Patchwork-Id: 11847449
Return-Path: <SRS0=07X0=D3=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-6.6 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=no autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 52AC9C4363A
	for <kvm@archiver.kernel.org>; Tue, 20 Oct 2020 17:01:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C89642177B
	for <kvm@archiver.kernel.org>; Tue, 20 Oct 2020 17:01:05 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="dDcwSXCO"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2395092AbgJTRBE (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 20 Oct 2020 13:01:04 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:35584 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2389544AbgJTRBE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 20 Oct 2020 13:01:04 -0400
Received: from mail-pj1-x1033.google.com (mail-pj1-x1033.google.com
 [IPv6:2607:f8b0:4864:20::1033])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id EFB08C0613CE
        for <kvm@vger.kernel.org>; Tue, 20 Oct 2020 10:01:03 -0700 (PDT)
Received: by mail-pj1-x1033.google.com with SMTP id a17so1207774pju.1
        for <kvm@vger.kernel.org>; Tue, 20 Oct 2020 10:01:03 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=SLjiq3pW5LVJISD8gSWpF8UZ/0csQIwTmjFHfpB8KGQ=;
        b=dDcwSXCOzydk78Lztu+93aKWlVV++2x4fn6ADurjE0nmYUMY3OTsi8b/HGLbIvHHmR
         wGE+3kYadp+qsRdmbCX2qV8gLCpVlHGHoXbOrt9JzPOXo/rqoTZbwIjlKsgNASxlBTHb
         tl/YfgqmLAVupq0bf6Vk4CNoyFAsaDl5e57P6gB5WdTagLSb1RT6rbsMhXQcz0jWjtLZ
         jQn94KeXoj+UuTv2hgguVyoARgOULZ2pvnzwuYNBLdlqxRCJxv9uPShEUKKbFVtaW+zw
         4S4g87U3K8T0Ps3LLJrhtIf84mk5BLXDsbNwEbcGs/RDJqyFGrEdi366TLCyxptCVrat
         ab8Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=SLjiq3pW5LVJISD8gSWpF8UZ/0csQIwTmjFHfpB8KGQ=;
        b=Z27593FB7fgBcrKZtwHbrPx6IWUb6zDtwUeE048sHDljcdTmETI3YC14ZSi8ttA2io
         Ghp/w5f8/K7i0tzHOtkY+RMHQ3MelCRvtIM37k70kvyH/J6opQr2f+FQST6P1FH/jjp4
         c35UkG/CxUWkgMdPLRePMJyPrRLE/uxfA2gEi93P18ZL68WqYeJr0HjJR2P6bbw0PnMk
         CjgLSY4OZ37+2fHYyAkHgPwFvsavWRXv0nAtlWv0n0cdYZXRUG429d+pbTRAr++AgkFP
         ntvwLJ9cJuGZ0x+yv8AIzUiq1SRD8GjphZHvRz6sjhqlwckpPwPn/8olsh9fBuESjyBV
         CPRQ==
X-Gm-Message-State: AOAM531aQ3TN3zom9KB7aketgzzDzFJvZXnkqEmQz7Py8bPmU6baPvkC
        RvFNesf5AhH7rM6S00EWyfq+OPOYMFw=
X-Google-Smtp-Source: 
 ABdhPJzXgH2W//CCXKxe46Ozb57JxmILIjseYynzoQ2X2SC2duR/Vzet5uVuIs+T4bHdhfZIYOLR9Q==
X-Received: by 2002:a17:90a:f0d7:: with SMTP id
 fa23mr3634676pjb.108.1603213263248;
        Tue, 20 Oct 2020 10:01:03 -0700 (PDT)
Received: from localhost.localdomain ([103.248.31.132])
        by smtp.googlemail.com with ESMTPSA id
 x29sm2766161pfp.152.2020.10.20.10.01.00
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 20 Oct 2020 10:01:02 -0700 (PDT)
From: Amey Narkhede <ameynarkhede03@gmail.com>
To: qemu-devel@nongnu.org, ameynarkhede03@gmail.com
Cc: "Michael S. Tsirkin" <mst@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>, kvm@vger.kernel.org,
        Paolo Bonzini <pbonzini@redhat.com>
Subject: [PATCH 0/2] KVM: Introduce ioeventfd read support
Date: Tue, 20 Oct 2020 22:30:54 +0530
Message-Id: <20201020170056.433528-1-ameynarkhede03@gmail.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The first patch updates linux headers to
add ioeventfd read support while the
second patch can be used to test the
ioeventfd read feature with kvm-unit-test
which reads from specified guest addres.
Make sure the address provided in
kvm_set_ioeventfd_read matches with address
in x86/ioeventfd_read test in kvm-unit-tests.

Amey Narkhede (2):
  linux-headers: Add support for reads in ioeventfd
  kvm: Add ioeventfd read test code

 accel/kvm/kvm-all.c       | 55 +++++++++++++++++++++++++++++++++++++++
 linux-headers/linux/kvm.h |  5 +++-
 2 files changed, 59 insertions(+), 1 deletion(-)
```
#### [PATCH v2 00/10] KVM: VMX: Clean up Hyper-V PV TLB flush
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Tue Oct 20 21:56:03 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11847977
Return-Path: <SRS0=07X0=D3=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-6.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=no autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0C42DC4363A
	for <kvm@archiver.kernel.org>; Tue, 20 Oct 2020 21:57:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B10972237B
	for <kvm@archiver.kernel.org>; Tue, 20 Oct 2020 21:57:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2438812AbgJTV4P (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 20 Oct 2020 17:56:15 -0400
Received: from mga12.intel.com ([192.55.52.136]:61050 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2392476AbgJTV4P (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 20 Oct 2020 17:56:15 -0400
IronPort-SDR: 
 KD7CokRLnyt00L9wBN2hbU7Roo3qbqkstUzirEsTb5DAQg5ZKUzK7xqZA3NhOtLPAdYHLlmkG2
 1xBJHPSgR8SA==
X-IronPort-AV: E=McAfee;i="6000,8403,9780"; a="146576322"
X-IronPort-AV: E=Sophos;i="5.77,399,1596524400";
   d="scan'208";a="146576322"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 20 Oct 2020 14:56:14 -0700
IronPort-SDR: 
 iDVYLwgQxcI2ZbABD9Tw1wZD6j2xT7flUafgrPfdVcCMGFBp6xVpGEX0YHjwGuHrLbSi44UlcJ
 IVdeqQbGG30g==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,399,1596524400";
   d="scan'208";a="301827710"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by fmsmga008.fm.intel.com with ESMTP; 20 Oct 2020 14:56:14 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2 00/10] KVM: VMX: Clean up Hyper-V PV TLB flush
Date: Tue, 20 Oct 2020 14:56:03 -0700
Message-Id: <20201020215613.8972-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Clean up KVM's PV TLB flushing when running with EPT on Hyper-V, i.e. as
a nested VMM.  No real goal in mind other than the sole patch in v1, which
is a minor change to avoid a future mixup when TDX also wants to define
.remote_flush_tlb.  Everything else is opportunistic clean up.

Ran Hyper-V KVM unit tests (if those are even relevant?), but haven't
actually tested on top of Hyper-V.

v2: Rewrite everything.

Sean Christopherson (10):
  KVM: VMX: Track common EPTP for Hyper-V's paravirt TLB flush
  KVM: VMX: Stash kvm_vmx in a local variable for Hyper-V paravirt TLB
    flush
  KVM: VMX: Fold Hyper-V EPTP checking into it's only caller
  KVM: VMX: Do Hyper-V TLB flush iff vCPU's EPTP hasn't been flushed
  KVM: VMX: Invalidate hv_tlb_eptp to denote an EPTP mismatch
  KVM: VMX: Don't invalidate hv_tlb_eptp if the new EPTP matches
  KVM: VMX: Explicitly check for hv_remote_flush_tlb when loading pgd
  KVM: VMX: Define Hyper-V paravirt TLB flush fields iff Hyper-V is
    enabled
  KVM: VMX: Skip additional Hyper-V TLB EPTP flushes if one fails
  KVM: VMX: Track PGD instead of EPTP for paravirt Hyper-V TLB flush

 arch/x86/kvm/vmx/vmx.c | 102 ++++++++++++++++++++---------------------
 arch/x86/kvm/vmx/vmx.h |  16 +++----
 2 files changed, 57 insertions(+), 61 deletions(-)
```
