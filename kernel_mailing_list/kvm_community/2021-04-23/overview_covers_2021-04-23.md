

#### [PATCH 0/4] KVM: x86: Kill off pdptrs_changed()
##### From: Sean Christopherson <seanjc@google.com>

```c
From patchwork Fri Apr 23 00:06:33 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12219263
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2BB97C433ED
	for <kvm@archiver.kernel.org>; Fri, 23 Apr 2021 00:06:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F1F4861155
	for <kvm@archiver.kernel.org>; Fri, 23 Apr 2021 00:06:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236068AbhDWAHR (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 22 Apr 2021 20:07:17 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:50860 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S235797AbhDWAHQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 22 Apr 2021 20:07:16 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 271B7C06174A
        for <kvm@vger.kernel.org>; Thu, 22 Apr 2021 17:06:41 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id
 f7-20020a5b0c070000b02904e9a56ee7e7so22046887ybq.9
        for <kvm@vger.kernel.org>; Thu, 22 Apr 2021 17:06:41 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=v66Jk+gEpeRgxxkcCt+o/qjQEpMd7xAYrLPcmO2p4cI=;
        b=VTxsg4h0oDCx7YbTDXvRJwivIso/3i16ryOJZvE2aLPAXwnNlMyYEX/xjLO65QNGnq
         UAWmt8fAh4j5/dxuDxyFeEP7NHUD2X1W0xTxJFuJ984FLTRQI2v2r29shPH1N66C2uKS
         b5p0PZPRzxa63ZguF4QbBvsH9mXOk5vpkzcYubnxNVrMUa3a1Anr5nS1yN42Q8rwn62m
         1mjb0FxpoDDLkAL1TZXgJzLI++X8PnErigmkdYmXmD7a2wr/egMfDrsllaG+o9jXsU23
         uy1sHv2Js6+L0X9k6abwbNoDVvOCaybixGMHokDHKp9M1sy0pbVZDW5iSnSZAV7x7vk3
         aB7Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:message-id:mime-version:subject
         :from:to:cc;
        bh=v66Jk+gEpeRgxxkcCt+o/qjQEpMd7xAYrLPcmO2p4cI=;
        b=QNyUSLk0i6Bj+kQwYR/hvzSDcbQx+hToCbOYpEp82VysEBbTG9ZpCzwDpRoGcoMj76
         vR0tJMhwx2IagaHqojt1/sqasSv3F1JG/PuwD/3ocbvYS3fBNWUsFb5e2xdG7uDu6/3F
         A0s91+5pxh3q2ZtAUTkSKcM/ck9Vbt52DQIHFfaiDa4cErdKl62KkvcrVkdS/d4rzGnN
         Hr2gL1bOr4NAIQJF8zaPRwA16RCUcLfzNjDFvZ5mwgskfgjuQQXCI4dRtBg+emwQktnF
         l0APQr/mmhsqtYh+Zxe6fYfkyocuY7Hcim04Tk48bksRjtU9ywcztHdUz9prEhV10QNV
         BiZg==
X-Gm-Message-State: AOAM533AifhSW+Djj4cs4CDYdMRjXfQsE08qq5dHElj+G9LZs42aIp0H
        IYTlEVKVd4v1gMDNCONoom2pXkmd5NY=
X-Google-Smtp-Source: 
 ABdhPJzadxessdpAjDDbX76aXuVMs4n1pAxeTI8YzDEJJFSYiKh/f16bzz2wlJzDr6iw5UeDcHZHJI7BPzg=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:e012:374c:592:6194])
 (user=seanjc job=sendgmr) by 2002:a25:680c:: with SMTP id
 d12mr122727ybc.87.1619136400249;
 Thu, 22 Apr 2021 17:06:40 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Thu, 22 Apr 2021 17:06:33 -0700
Message-Id: <20210423000637.3692951-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.498.g6c1eba8ee3d-goog
Subject: [PATCH 0/4] KVM: x86: Kill off pdptrs_changed()
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Remove pdptrs_changed(), which is mostly dead anyways, and the few bits
that are still thrashing are useless.

This conflicts with Maxim's work to migrate PDPTRs out-of-band, but I
think it will conflict in a good way as the "skip load_pdptrs()"
logic for the out-of-band case won't have to juggle this legacy crud.

Sean Christopherson (4):
  KVM: nVMX: Drop obsolete (and pointless) pdptrs_changed() check
  KVM: nSVM: Drop pointless pdptrs_changed() check on nested transition
  KVM: x86: Always load PDPTRs on CR3 load for SVM w/o NPT and a PAE
    guest
  KVM: x86: Unexport kvm_read_guest_page_mmu()

 arch/x86/include/asm/kvm_host.h |  4 ----
 arch/x86/kvm/svm/nested.c       |  6 ++---
 arch/x86/kvm/vmx/nested.c       |  8 +++----
 arch/x86/kvm/x86.c              | 41 ++++-----------------------------
 4 files changed, 10 insertions(+), 49 deletions(-)
```
#### [PATCH 0/3] KVM: selftests: arm64 exception handling and debug test
##### From: Ricardo Koller <ricarkol@google.com>

```c
From patchwork Fri Apr 23 04:03:48 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ricardo Koller <ricarkol@google.com>
X-Patchwork-Id: 12219529
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 51A3BC433B4
	for <kvm@archiver.kernel.org>; Fri, 23 Apr 2021 04:04:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2C1B26144A
	for <kvm@archiver.kernel.org>; Fri, 23 Apr 2021 04:04:00 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229639AbhDWEEf (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 23 Apr 2021 00:04:35 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:46058 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229454AbhDWEEe (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 23 Apr 2021 00:04:34 -0400
Received: from mail-pf1-x449.google.com (mail-pf1-x449.google.com
 [IPv6:2607:f8b0:4864:20::449])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 02B3DC061574
        for <kvm@vger.kernel.org>; Thu, 22 Apr 2021 21:03:59 -0700 (PDT)
Received: by mail-pf1-x449.google.com with SMTP id
 d130-20020a621d880000b02901fb88abc171so14311426pfd.11
        for <kvm@vger.kernel.org>; Thu, 22 Apr 2021 21:03:58 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=X+DkTW1449q6fKkD8wwhLKFk8s0Ll4r+obcvc3w7AoY=;
        b=OEV2E0v7G6MTuZNr6BG8lG5sW3RKvFodkb/XgGwjBktiRnkXbRKMRqYz/lzohVAI/E
         r0/P7Urx2zN0iq9Jdq1FmN1WGG1A5vrWPFfQUPwM4XG2URDsvLGMfF7S28OSkRSjzps3
         04lQmvsAPgbiSzxoWjwXj140V2pmVwFbjk+ghVUQKxCl08oYu6FnI7a1a5DZCRi+mQIY
         O5I4ztfWmfkqO6XXsiGqHZYAxikvGeNU+p0DymtFax1b+HaddNSHuf+bdzBbPPSaDLp2
         ii0FukZCzTcycFtCxy8Fx5BYQtUh1pfkcX/t6pmuyfORPa3PyGh+9eN6IuKUc4jojNNb
         XqGw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=X+DkTW1449q6fKkD8wwhLKFk8s0Ll4r+obcvc3w7AoY=;
        b=Y1qvzJEVos76C+dMQyvrlUZaIrQ4NBZ4YcuaAc/2Zq4Q3q6NLFdbss9pMxuNpzuOWN
         z+5Gt2k8CvCaSgIxR6aZieSE0x95uqNuVY36eAEEuu6mZpW6kbwEyuQLJqN+8KuJBZvn
         05MPVoryys7+YLIg1mh+OXAzhGNwDvVrPI9jZxqHju7deA5vSMa9sEovXPFh+0Ob0y84
         HK5UDrJmB9mta9Gr+BwcsMPuiDOdIMp73IbvcSS3Ic96Ue0rE67JNrEL/qLo5hOmfb2F
         75LToug5h1qeWIb8d8iFu2boSbPP3bkKYGBFB8//785IUXzcopyKtRLIoyh4abj6tE/U
         Bbeg==
X-Gm-Message-State: AOAM5304KSbuMnRdK66hwRRa/HtxsQOliEa460Ohm/TXvFJ/5wY0xsIJ
        a5Q4sircMZV8oXMQKsmc0OGJKDJvcgY2zrTtD7H82KxS6B3VVfaA3lvxRVW4t3t4qzdzIKjgLoe
        kQxA626fHbV9ltwH+efqV9DPHE4anQQwZF5uAmUMFldmYHex/3mweIcwyi+P+Mlw=
X-Google-Smtp-Source: 
 ABdhPJzAqfVay/TiQ2no35LKS+c6fnp/vF6u7i0f38OpLvhcyqzJZ1aTWQmi2aj2SkJiYTFhn+EdPXPQ/sludw==
X-Received: from ricarkol2.c.googlers.com
 ([fda3:e722:ac3:10:24:72f4:c0a8:62fe])
 (user=ricarkol job=sendgmr) by 2002:a17:90b:19d1:: with SMTP id
 nm17mr3454828pjb.218.1619150637213; Thu, 22 Apr 2021 21:03:57 -0700 (PDT)
Date: Thu, 22 Apr 2021 21:03:48 -0700
Message-Id: <20210423040351.1132218-1-ricarkol@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.498.g6c1eba8ee3d-goog
Subject: [PATCH 0/3] KVM: selftests: arm64 exception handling and debug test
From: Ricardo Koller <ricarkol@google.com>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
Cc: pbonzini@redhat.com, maz@kernel.org, drjones@redhat.com,
        alexandru.elisei@arm.com, eric.auger@redhat.com,
        Ricardo Koller <ricarkol@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

These patches add a debug exception test in aarch64 KVM selftests while
also adding basic exception handling support.

The structure of the exception handling is based on its x86 counterpart.
Tests use the same calls to initialize exception handling.  And both
architectures use vm_handle_exception() to override the handler for a
particular vector, or (vector, ec) in the arm64 case.

The debug test is similar to x86_64/debug_regs, except that the x86 one
controls the debugging from outside the VM. This proposed arm64 test
controls and handles debug exceptions from the inside.

The final patch adapts the x86 unhandled-vector reporting to use the
same mechanism as the one introduced for arm64 (UCALL_UNHANDLED instead
of direct x86 port IO).

Thanks,
Ricardo

Ricardo Koller (3):
  KVM: selftests: Add exception handling support for aarch64
  KVM: selftests: Add aarch64/debug-exceptions test
  KVM: selftests: Use a ucall for x86 unhandled vector reporting

 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   3 +-
 .../selftests/kvm/aarch64/debug-exceptions.c  | 250 ++++++++++++++++++
 .../selftests/kvm/include/aarch64/processor.h |  86 ++++++
 .../testing/selftests/kvm/include/kvm_util.h  |   1 +
 .../selftests/kvm/include/x86_64/processor.h  |   2 -
 .../selftests/kvm/lib/aarch64/handlers.S      | 104 ++++++++
 .../selftests/kvm/lib/aarch64/processor.c     |  56 ++++
 .../selftests/kvm/lib/x86_64/processor.c      |  15 +-
 9 files changed, 506 insertions(+), 12 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/aarch64/debug-exceptions.c
 create mode 100644 tools/testing/selftests/kvm/lib/aarch64/handlers.S
```
#### [RFC PATCH V2 0/7] Do not read from descripto ring
##### From: Jason Wang <jasowang@redhat.com>

```c
From patchwork Fri Apr 23 08:09:35 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 12219837
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-10.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4615BC433B4
	for <kvm@archiver.kernel.org>; Fri, 23 Apr 2021 08:10:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E55966128A
	for <kvm@archiver.kernel.org>; Fri, 23 Apr 2021 08:10:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230192AbhDWIKt (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 23 Apr 2021 04:10:49 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:30387 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S229456AbhDWIKt (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 23 Apr 2021 04:10:49 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1619165412;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=Pc9kV6aoLVJwEsHfUpicjnbTw0ZNIpHRhnJgCa+FrJA=;
        b=OtEv4XoTxMJQhpqtfkWCUNClYEEkLIYt+cqWjWO6/bOHfp8BriF87Ib7ofu+ICmfb66a1/
        NddbT+U9I476oTfBjfinzjYLN55LsdduLpnpHqXAKcvWr1OacPNN4nBSATYSf5FYDKoUEn
        S/tKHaQs3v2kGCClljNIWvkbcR8vRGg=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-414-j7lbdBtfOrKGXOLEB8R-Vw-1; Fri, 23 Apr 2021 04:10:08 -0400
X-MC-Unique: j7lbdBtfOrKGXOLEB8R-Vw-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 0A2D484BA42;
        Fri, 23 Apr 2021 08:10:07 +0000 (UTC)
Received: from localhost.localdomain (ovpn-13-225.pek2.redhat.com
 [10.72.13.225])
        by smtp.corp.redhat.com (Postfix) with ESMTP id A28A25C6DE;
        Fri, 23 Apr 2021 08:09:44 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: mst@redhat.com, jasowang@redhat.com
Cc: virtualization@lists.linux-foundation.org,
        linux-kernel@vger.kernel.org, xieyongji@bytedance.com,
        stefanha@redhat.com, file@sect.tu-berlin.de, ashish.kalra@amd.com,
        konrad.wilk@oracle.com, kvm@vger.kernel.org, hch@infradead.org
Subject: [RFC PATCH V2 0/7] Do not read from descripto ring
Date: Fri, 23 Apr 2021 16:09:35 +0800
Message-Id: <20210423080942.2997-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi:

Sometimes, the driver doesn't trust the device. This is usually
happens for the encrtpyed VM or VDUSE[1]. In both cases, technology
like swiotlb is used to prevent the poking/mangling of memory from the
device. But this is not sufficient since current virtio driver may
trust what is stored in the descriptor table (coherent mapping) for
performing the DMA operations like unmap and bounce so the device may
choose to utilize the behaviour of swiotlb to perform attacks[2].

To protect from a malicous device, this series store and use the
descriptor metadata in an auxiliay structure which can not be accessed
via swiotlb instead of the ones in the descriptor table. This means
the descriptor table is write-only from the view of the driver.

Actually, we've almost achieved that through packed virtqueue and we
just need to fix a corner case of handling mapping errors. For split
virtqueue we just follow what's done in the packed.

Note that we don't duplicate descriptor medata for indirect
descriptors since it uses stream mapping which is read only so it's
safe if the metadata of non-indirect descriptors are correct.

For split virtqueue, the change increase the footprint due the the
auxiliary metadata but it's almost neglectlable in the simple test
like pktgen or netpef.

Slightly tested with packed on/off, iommu on/of, swiotlb force/off in
the guest.

Please review.

Changes from V1:
- Always use auxiliary metadata for split virtqueue
- Don't read from descripto when detaching indirect descriptor

[1]
https://lore.kernel.org/netdev/fab615ce-5e13-a3b3-3715-a4203b4ab010@redhat.com/T/
[2]
https://yhbt.net/lore/all/c3629a27-3590-1d9f-211b-c0b7be152b32@redhat.com/T/#mc6b6e2343cbeffca68ca7a97e0f473aaa871c95b

Jason Wang (7):
  virtio-ring: maintain next in extra state for packed virtqueue
  virtio_ring: rename vring_desc_extra_packed
  virtio-ring: factor out desc_extra allocation
  virtio_ring: secure handling of mapping errors
  virtio_ring: introduce virtqueue_desc_add_split()
  virtio: use err label in __vring_new_virtqueue()
  virtio-ring: store DMA metadata in desc_extra for split virtqueue

 drivers/virtio/virtio_ring.c | 201 +++++++++++++++++++++++++----------
 1 file changed, 144 insertions(+), 57 deletions(-)
```
#### [PATCH v2 0/4] Add guest support for SEV live migration.
##### From: Ashish Kalra <Ashish.Kalra@amd.com>
From: Ashish Kalra <ashish.kalra@amd.com>

```c
From patchwork Fri Apr 23 15:57:37 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ashish Kalra <Ashish.Kalra@amd.com>
X-Patchwork-Id: 12220817
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 19A87C433ED
	for <kvm@archiver.kernel.org>; Fri, 23 Apr 2021 15:57:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D545C613F2
	for <kvm@archiver.kernel.org>; Fri, 23 Apr 2021 15:57:54 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S242868AbhDWP6a (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 23 Apr 2021 11:58:30 -0400
Received: from mail-bn7nam10on2040.outbound.protection.outlook.com
 ([40.107.92.40]:30177
        "EHLO NAM10-BN7-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S230294AbhDWP63 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 23 Apr 2021 11:58:29 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=Hj8qwmi4AJr8VBRVDxxcenvzfJfDXSk3q4SRKBmQmMvMayr7bHuYUdEw+MVeVdjVVWzHlMxzkXqJBYoLxCmIZFe9dpWTi77pbhkuV24FQL0MnsUD1JVk6lVg1Yh5G1ZA46wLzfXEu3Wx+mg+RUAivvvXwtxLFNwH+GLzYS/YwSdkXpugfDbZ4MuTBzCnFBi9jfnRWYGgRF3TNCxwnp4CJQJNDSgkmEzOTc8goH3/ceNK/SeX5aiT2iGXd/+TJS+0u5l8RaK18i7fyH7H14BeX7xOyxSVMWJjZ2MiNpAxJW+D8csHTxlcvcmD19WmL3dAUJsfp2s9GmzcMOhrw2kZVg==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=F53DxMEmTDauDiuBiayNoqFb/H5LiJjzcRFK40j+zLc=;
 b=k5B5TejZ8q+GFAJ8Sc63jpsHiBF4aLlGF9Wd871PgzSB7LXfDgn3buT77r+ToewSounmvEWAtgpuwRbmTA7oLO7t86tfEIQ0QO+ZXY+wzl4DzisEWCkCw410ayvBk6TCT+sxRB3yGR4hQiT4YCnXoqSXCYlyydQ0xb39MsizwekeK3daNrf5gI8eimkb3CoObDrYkqP3+N4XH2xYfqZOs1wp69w3GCrevjMvJqfUFseobfNyRSfjaCdtItrv3vgWqpbdF3fMainaqPm2s4QRa/KMLOjPtfeyo2SUOQSotGwg//Y6yakaWG+Gc3s0pj10WdCQI0sS7guULLAhMdplHg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=amd.com; s=selector1;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=F53DxMEmTDauDiuBiayNoqFb/H5LiJjzcRFK40j+zLc=;
 b=tsUKZKvq2ga2HSGMkEoHtmXVWZ1+NLsyYvGFliWCURgGzLbfzgSxnN+kxkqDQlWBHst7WwVsz9VWo+FblhQyzVAx7d/xG8B/ua7cWpieglIHLm725owd0aW4xkoTZq2IsYEiTLAl3yFwSWJE8lCwav5QtEybscVRx2tBefrhFtM=
Authentication-Results: redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=none action=none header.from=amd.com;
Received: from SN6PR12MB2767.namprd12.prod.outlook.com (2603:10b6:805:75::23)
 by SN1PR12MB2510.namprd12.prod.outlook.com (2603:10b6:802:28::26) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4065.23; Fri, 23 Apr
 2021 15:57:48 +0000
Received: from SN6PR12MB2767.namprd12.prod.outlook.com
 ([fe80::1fb:7d59:2c24:615e]) by SN6PR12MB2767.namprd12.prod.outlook.com
 ([fe80::1fb:7d59:2c24:615e%7]) with mapi id 15.20.4065.025; Fri, 23 Apr 2021
 15:57:48 +0000
From: Ashish Kalra <Ashish.Kalra@amd.com>
To: pbonzini@redhat.com
Cc: tglx@linutronix.de, mingo@redhat.com, hpa@zytor.com,
        joro@8bytes.org, bp@suse.de, thomas.lendacky@amd.com,
        x86@kernel.org, kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        srutherford@google.com, seanjc@google.com,
        venu.busireddy@oracle.com, brijesh.singh@amd.com
Subject: [PATCH v2 0/4] Add guest support for SEV live migration.
Date: Fri, 23 Apr 2021 15:57:37 +0000
Message-Id: <cover.1619193043.git.ashish.kalra@amd.com>
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SN6PR2101CA0022.namprd21.prod.outlook.com
 (2603:10b6:805:106::32) To SN6PR12MB2767.namprd12.prod.outlook.com
 (2603:10b6:805:75::23)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ashkalra_ubuntu_server.amd.com (165.204.77.1) by
 SN6PR2101CA0022.namprd21.prod.outlook.com (2603:10b6:805:106::32) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4108.1 via Frontend
 Transport; Fri, 23 Apr 2021 15:57:47 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 42598c91-4627-4b6d-ab9d-08d906708a85
X-MS-TrafficTypeDiagnostic: SN1PR12MB2510:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SN1PR12MB25101F90E197B04088A803448E459@SN1PR12MB2510.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:8882;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 Lb+wb4rligL5vLiECCCipSmM0bhFPJk1DA4Od35vONcrFTyFlcTUhfV28nDozhPse/QQ0dYCedGLkxjO7aIzWqHdjW7k6vCf11lLMrWhDzQHk3omB0C3om5PoVuonJQrFfwsacmp6ccllUXsd/OoMg9Io/7QFJ/CvZuU3lx95e77ooFc6Bd+RoEBqV76IyRibsTxnIEmevdzRudi4gDe+2LkqD+R4jhPp1W42B4enc/FXQVrrSW9AqXD5j8rzd+sG4HDq2m7ViB1uTS+nM2y07fJMwU+j95M9RaivqJnPZxzkmQOOtPNJvX7SNOU7g3m83f1Nx1hXIvQK/rTzLLYjp9aRTa7aLd8zqDhyaxYMN8TIKdeSaeJJtHME1KZNT7b8EsjYMYWbtBC9MrBknPeNeOiMyBfAqpnE/9ZM1K0BQi7/yrqySZnUqEdAG16mP5BDrKW0r+MwRK4t8It0HDWE0xsQ2nds540LZ2icPCUU9f8V1XzzFfohs/WRJbuWR4lEj9rgLoST8I5WOxDqktO4sGsfy01Bh3TPWBiamld9Ym1rLvkNo7pLQTrY/Tb2sQS6r45ojtodpTpd4ZyAkXUxSAT1JQbuYqPfZj79lRTLy9hxsI/CE0l1rjlBJsePUsJcQlc007sV0OeoOa+LzrPDA==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR12MB2767.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(346002)(396003)(376002)(39860400002)(136003)(366004)(52116002)(186003)(478600001)(38100700002)(38350700002)(26005)(16526019)(7696005)(8936002)(6666004)(6486002)(316002)(86362001)(7416002)(2906002)(8676002)(5660300002)(6916009)(4326008)(36756003)(66946007)(83380400001)(956004)(2616005)(66556008)(66476007);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 6D3makMF8kwQCjRcBu3Cr8YTdXMCDwi8hz0JrKamtpmwbU91iex5Jk9mpWzJEJdj3AsNfOhk6tzuFZyafCGrryvJf28GcfGY4Y/OnzxNAKQ8L6YxcRXgH+r4XO6hMiD4BlDmDm85lUYdwepsfiovioauoO7uns8tzz99mPkohOOneh5rKugjZ/Ae1OaLhBacBAme6IZtmfc6jBKmXVVC8D2331x0IM7vCXQT5UBjRbL38mV3mcRod2iWPa+ePnPKYGbtyqXBxeIihI7UVzj89mXVZ3EWdzdLdyM1Mk6xInngZ9i14J6NRClbqNJKj6Cjo/ed3eVj85BC55kUzlIKXjHEoshR++kXpwLN410SuywEkDtzmltKZOoZzikeQecQ0fvZ09m+9+UjkQAe3VFHQu5eZbJz8ua0pKmyGn9owqSIPdDyKuQIeLvoEM1kXy009oQAFiiSQXgd7t3x/fcWUcs+0N5K//HB0eiF3z1sM3xsziyzJcjaJJXfiySFkR7qZR1ogBNFJp9NRtaySXuhh9GvkS0nk6o9dULvVBI1/JpNkNXGyalf/Q13jS5zebsnnX19fUcs5kzkp4ROWTyH8abUj+tQ9AtNIIhXN7Zqgawr0swL0d6/m0XL9o5hXNtZr0Serx2pmv0WK3Lw2GcOSNJcTHdPO+e2Aqj9CB7lSXoWBLFAAfk3xGgb6HMGF9pTrd2JGhg4dJG+JO2guXlj5nF88ZaJH3PPJNYorXNOGmp5YSEdByks40qgyvfO3vHkbIggHIGyoiLO8JqK4o1Z31tRMeEp3X+A9dDfe5SBE9kvr1PmWhdX55L7Te5UBITlLzOK9iU4Vv016cc7+J+Y07tdcJUXGy7NcaknLEkeynU5rAjm0RmaLTPBPNu1HLboYr9f+FX7QwdGhC/53blGwyBtavZgo/phwZ4UGWgA8TGPVYuXVU2ULbaOHUM4g6Xc0Am8WK7RwtjiUdJxXSHLwUOBFLpl8lTPz/YQI8oa7SlY341T5aq2D2J+sR/X8yW0PR6x5AQQgiJ5J3yLGC5a7Qb8qwSeo3vYk235n1mkfbfytLImlSGDhZttqMVMyneSQRy7buAb4sXbg+i7mOZY422frs8EWLfyWYrxK2oKLEqH4xpna/HeOg9xt+xNvE11iIyGUR/6ENJrV4xp5ZHq8Y+V/z0ZUiAOhN8JofHo7s1lBBA36YAVgcWXnKv+HQ4AxG/xCB9P7JXEPUiEjvjueMazV21amTjwM86LS4czOv5RS6B9fyhPbTgcypD6wfsn7quZIEayy2qTNi1/06O2U9Op9DdHnJnvzDENZRXwbddJ9jHajsBjmivT1TyI9V/T
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 42598c91-4627-4b6d-ab9d-08d906708a85
X-MS-Exchange-CrossTenant-AuthSource: SN6PR12MB2767.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 23 Apr 2021 15:57:48.2084
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 Fyy4rZQwBNd5dBISWgnbIv8kquIyqL1XvMD5TtpwoUGXm5x8eJIzFntvgb1u2B5cxCJK1TyrazIXULUqiz2yYQ==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SN1PR12MB2510
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Ashish Kalra <ashish.kalra@amd.com>

The series adds guest support for SEV live migration.

The patch series introduces a new hypercall. The guest OS can use this
hypercall to notify the page encryption status. If the page is encrypted
with guest specific-key then we use SEV command during the migration.
If page is not encrypted then fallback to default.

This section descibes how the SEV live migration feature is negotiated
between the host and guest, the host indicates this feature support via 
KVM_FEATURE_CPUID. The guest firmware (OVMF) detects this feature and
sets a UEFI enviroment variable indicating OVMF support for live
migration, the guest kernel also detects the host support for this
feature via cpuid and in case of an EFI boot verifies if OVMF also
supports this feature by getting the UEFI enviroment variable and if it
set then enables live migration feature on host by writing to a custom
MSR, if not booted under EFI, then it simply enables the feature by
again writing to the custom MSR.

Changes since v1:
 - Avoid having an SEV specific variant of kvm_hypercall3() and instead
   invert the default to VMMCALL.

Ashish Kalra (3):
  KVM: x86: invert KVM_HYPERCALL to default to VMMCALL
  EFI: Introduce the new AMD Memory Encryption GUID.
  x86/kvm: Add guest support for detecting and enabling SEV Live
    Migration feature.

Brijesh Singh (1):
  mm: x86: Invoke hypercall when page encryption status is changed

 arch/x86/include/asm/kvm_para.h       |   2 +-
 arch/x86/include/asm/mem_encrypt.h    |   4 +
 arch/x86/include/asm/paravirt.h       |   6 ++
 arch/x86/include/asm/paravirt_types.h |   2 +
 arch/x86/include/asm/set_memory.h     |   2 +
 arch/x86/kernel/kvm.c                 | 106 ++++++++++++++++++++++++++
 arch/x86/kernel/paravirt.c            |   1 +
 arch/x86/mm/mem_encrypt.c             |  72 ++++++++++++++---
 arch/x86/mm/pat/set_memory.c          |   7 ++
 include/linux/efi.h                   |   1 +
 10 files changed, 193 insertions(+), 10 deletions(-)
```
#### [PATCH v3 0/4] KVM statistics data fd-based binary interface
##### From: Jing Zhang <jingzhangos@google.com>

```c
From patchwork Fri Apr 23 18:17:23 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jing Zhang <jingzhangos@google.com>
X-Patchwork-Id: 12221283
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id CD03CC43470
	for <kvm@archiver.kernel.org>; Fri, 23 Apr 2021 18:17:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2097961467
	for <kvm@archiver.kernel.org>; Fri, 23 Apr 2021 18:17:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S243644AbhDWSSM (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 23 Apr 2021 14:18:12 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:36608 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S243653AbhDWSSJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 23 Apr 2021 14:18:09 -0400
Received: from mail-pf1-x449.google.com (mail-pf1-x449.google.com
 [IPv6:2607:f8b0:4864:20::449])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id AB3FEC06138F
        for <kvm@vger.kernel.org>; Fri, 23 Apr 2021 11:17:31 -0700 (PDT)
Received: by mail-pf1-x449.google.com with SMTP id
 a16-20020aa786500000b0290257e9832af4so13486680pfo.5
        for <kvm@vger.kernel.org>; Fri, 23 Apr 2021 11:17:31 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=jZ9aELeTtebSkfbpomfAFciujOueU+/1u2IVpj9kO9Q=;
        b=RyBxs7miM4jdCQ3yugSc8OvrTlv5u+dF3p+Ra7seVMrj1RVtjB+pFXakJoRIl1jsLS
         4JBtMKLiNnj9NnUNB9BsPmg2GgDdmytyBuu/qlKens774np+kb3bnNCuXir7AcEhlc1/
         MMqfYw4RQYaFjE94XkSwKSrhOxKcqkWzlvWkJUaoPIQajn3YTSQmT7PSjqoq+mzFElwD
         Nmi2pZp5/s1xwbLuQYIu7SednNnDgqlgHAbjSb3Ng+chogeOuRdzvwODmr0TjSFEqRbh
         /2xlGDh8qLD5AOsfQQHMcbZvPA7WcxPJHgBTYDJjHZfxvE6utLgsp5D6rJBK8yPps95G
         xQ1A==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=jZ9aELeTtebSkfbpomfAFciujOueU+/1u2IVpj9kO9Q=;
        b=ecmDyuYcr5f8j1Y9DPrhvVdjRwfnEwkwcAAmrCi1UZjlYlV0ZoBbGvEbiaQpKzLnE2
         xGF4vTsx0Y7MDBys1VbMBgWvKMU7Z3DEnTk2qdKuucc6iKu5Ug57hCnO8PIHfiwr5bFd
         Ti0v0KQu7OP6NNpSLM6JrXosJdiV4iCf5zIC+5+P6YZDXT7bSMUnomKjzYx/DHzmR4I6
         e+fdISbBwfj4QooLeBTSNqWnn3lBJfbKvxvE3nUjovmEw/wacpkBU09RL+tc6TYu5q5L
         eq3zzsRHMTluidQayJoXkZB/Y+uAsQzi1kuHL0JCV0rl7gBUzeUyHpUrwG6joZlTe1aR
         Mjww==
X-Gm-Message-State: AOAM531UtdgrNBzHR1xZEAn3tXFuGXh9gFEoibhy3S37/O5LWYSXUE+Y
        nBCDLc/BUfk8z1y4XQXK76Nsl6fOdJulrouQFqToSiph6i6LPJd1MnK3UdL1LOvwUbJFRLec7bO
        Seutnr+U5zYaOnn3qqzrBWPPUn+bcezvbFWPJBr1sqkVAHypG7i4ZzXSFXWHsZoHsXc1Id7k=
X-Google-Smtp-Source: 
 ABdhPJybLPMWN/SpAe3p+WeheeiGCmvt6zlmflTWrm4w6vD8liP2VaphrDYff46dFN5dJ0IrExvz0uL99CbVXXMV7Q==
X-Received: from jgzg.c.googlers.com ([fda3:e722:ac3:10:7f:e700:c0a8:1acf])
 (user=jingzhangos job=sendgmr) by 2002:a17:90b:e98:: with SMTP id
 fv24mr1049588pjb.1.1619201850403; Fri, 23 Apr 2021 11:17:30 -0700 (PDT)
Date: Fri, 23 Apr 2021 18:17:23 +0000
Message-Id: <20210423181727.596466-1-jingzhangos@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.498.g6c1eba8ee3d-goog
Subject: [PATCH v3 0/4] KVM statistics data fd-based binary interface
From: Jing Zhang <jingzhangos@google.com>
To: KVM <kvm@vger.kernel.org>, KVMARM <kvmarm@lists.cs.columbia.edu>,
        LinuxMIPS <linux-mips@vger.kernel.org>,
        KVMPPC <kvm-ppc@vger.kernel.org>,
        LinuxS390 <linux-s390@vger.kernel.org>,
        Linuxkselftest <linux-kselftest@vger.kernel.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Marc Zyngier <maz@kernel.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Will Deacon <will@kernel.org>,
        Huacai Chen <chenhuacai@kernel.org>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>,
        Thomas Bogendoerfer <tsbogend@alpha.franken.de>,
        Paul Mackerras <paulus@ozlabs.org>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Claudio Imbrenda <imbrenda@linux.ibm.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Peter Shier <pshier@google.com>,
        Oliver Upton <oupton@google.com>,
        David Rientjes <rientjes@google.com>,
        Emanuele Giuseppe Esposito <eesposit@redhat.com>
Cc: Jing Zhang <jingzhangos@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset provides a file descriptor for every VM and VCPU to read
KVM statistics data in binary format.
It is meant to provide a lightweight, flexible, scalable and efficient
lock-free solution for user space telemetry applications to pull the
statistics data periodically for large scale systems. The pulling
frequency could be as high as a few times per second.
In this patchset, every statistics data are treated to have some
attributes as below:
  * architecture dependent or common
  * VM statistics data or VCPU statistics data
  * type: cumulative, instantaneous,
  * unit: none for simple counter, nanosecond, microsecond,
    millisecond, second, Byte, KiByte, MiByte, GiByte. Clock Cycles
Since no lock/synchronization is used, the consistency between all
the statistics data is not guaranteed. That means not all statistics
data are read out at the exact same time, since the statistics date
are still being updated by KVM subsystems while they are read out.
---

* v2 -> v3
  - Rebase to kvm/queue, commit edf408f5257b ("KVM: avoid "deadlock" between
    install_new_memslots and MMU notifier")
  - Resolve some nitpicks about format

* v1 -> v2
  - Use ARRAY_SIZE to count the number of stats descriptors
  - Fix missing `size` field initialization in macro STATS_DESC

[1] https://lore.kernel.org/kvm/20210402224359.2297157-1-jingzhangos@google.com
[2] https://lore.kernel.org/kvm/20210415151741.1607806-1-jingzhangos@google.com

---

Jing Zhang (4):
  KVM: stats: Separate common stats from architecture specific ones
  KVM: stats: Add fd-based API to read binary stats data
  KVM: stats: Add documentation for statistics data binary interface
  KVM: selftests: Add selftest for KVM statistics data binary interface

 Documentation/virt/kvm/api.rst                | 171 ++++++++
 arch/arm64/include/asm/kvm_host.h             |   9 +-
 arch/arm64/kvm/guest.c                        |  42 +-
 arch/mips/include/asm/kvm_host.h              |   9 +-
 arch/mips/kvm/mips.c                          |  67 +++-
 arch/powerpc/include/asm/kvm_host.h           |   9 +-
 arch/powerpc/kvm/book3s.c                     |  68 +++-
 arch/powerpc/kvm/book3s_hv.c                  |  12 +-
 arch/powerpc/kvm/book3s_pr.c                  |   2 +-
 arch/powerpc/kvm/book3s_pr_papr.c             |   2 +-
 arch/powerpc/kvm/booke.c                      |  63 ++-
 arch/s390/include/asm/kvm_host.h              |   9 +-
 arch/s390/kvm/kvm-s390.c                      | 133 ++++++-
 arch/x86/include/asm/kvm_host.h               |   9 +-
 arch/x86/kvm/x86.c                            |  71 +++-
 include/linux/kvm_host.h                      | 132 ++++++-
 include/linux/kvm_types.h                     |  12 +
 include/uapi/linux/kvm.h                      |  50 +++
 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   3 +
 .../testing/selftests/kvm/include/kvm_util.h  |   3 +
 .../selftests/kvm/kvm_bin_form_stats.c        | 370 ++++++++++++++++++
 tools/testing/selftests/kvm/lib/kvm_util.c    |  11 +
 virt/kvm/kvm_main.c                           | 237 ++++++++++-
 24 files changed, 1405 insertions(+), 90 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/kvm_bin_form_stats.c


base-commit: edf408f5257ba39e63781b820528e1ce1ec0f543
```
#### [PATCH v3 0/4] KVM: x86: MSR_TSC_AUX fixes and improvements
##### From: Sean Christopherson <seanjc@google.com>

```c
From patchwork Fri Apr 23 22:34:00 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12221937
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5D334C433B4
	for <kvm@archiver.kernel.org>; Fri, 23 Apr 2021 22:34:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2F32B613DE
	for <kvm@archiver.kernel.org>; Fri, 23 Apr 2021 22:34:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S244125AbhDWWfG (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 23 Apr 2021 18:35:06 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:36194 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232806AbhDWWey (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 23 Apr 2021 18:34:54 -0400
Received: from mail-qv1-xf4a.google.com (mail-qv1-xf4a.google.com
 [IPv6:2607:f8b0:4864:20::f4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 027F3C06174A
        for <kvm@vger.kernel.org>; Fri, 23 Apr 2021 15:34:12 -0700 (PDT)
Received: by mail-qv1-xf4a.google.com with SMTP id
 f7-20020a0562141d27b029019a6fd0a183so19367620qvd.23
        for <kvm@vger.kernel.org>; Fri, 23 Apr 2021 15:34:11 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=m6vJDTZh9Y+DWagifmx06cOkYlWeKqEnHAb9nbqa1eA=;
        b=CcRHYOxRXnTeyAVKtPEMTQinsgIPUinhJmw50/VjAVx0sHoMnBHFxt4xxBAzhbSZVd
         sENXQVewfxQg75TVjm+J51qqFaMgyXnZVyw/SIZ1W+f7t7oVrs9SWCYS+tZST9scSCr7
         OTg6K1O+cQNXEiSVv+HncalpXuhgJT77Nv//jU7Sp4qTJcXSatGXfyRH8JkZdmWmNxXk
         TEE2dI8CM3Fzx4Fdu0+XGZ3Yci140NegEICdP84q+viRUGd1ipq8FJYNAKOgKx5lvgxr
         dmAgZ+F4Jq4HZ5P3INtAFPTVQ/sCB6CpVKt/7Njt0HM7+2JFQRhh+223JvXKSyI+sH8n
         bFlQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:message-id:mime-version:subject
         :from:to:cc;
        bh=m6vJDTZh9Y+DWagifmx06cOkYlWeKqEnHAb9nbqa1eA=;
        b=RB63Gx1zisVppmnUigDYV1d+FLn03C1YR7XG2Yj/+qRYBMg3zEHR9gr5ObVR1/N/jA
         bxFFYTIZAHur+zOyPCkg9hCAomaOSODJx0VRNczEJh0kl4QoPjEVtUmHl6pvQ7MuB5BH
         IKoEWeVMGspzBteCgBA8QOqUPMEXZUAppQXkga9w40LwQUmNjcbxIE9nHEMMVVqp+aTy
         BPZlG9kfnZNblfQ7Q3iJNm1tyMuKCuGHGlv1coFamEv2uiaTHYRwlegDidvK2JBTNnYy
         EfClYg0vhZ2e753p/FwgSeEKNIKZ4TwT4BJDRYTku3OL0fGQZ6jZhrAvBPkcN7fUO5hZ
         0ZOg==
X-Gm-Message-State: AOAM530X8XU5/HnlQhdXwBH1sVF+NwwsSNOTkB13ObQ8b+dNWHCbOHqo
        QlG8Vp5DICxU+/JZmjC3o6dS2TJhp/s=
X-Google-Smtp-Source: 
 ABdhPJz2JaYjQg+M5aZIzXLOM6Yt0ZXJrk6bikDyhR8ewjoF5usQ78BsWJrMhwWlVO57AGSylWfnzdGbc1U=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:ad52:3246:e190:f070])
 (user=seanjc job=sendgmr) by 2002:a0c:ecca:: with SMTP id
 o10mr7044437qvq.52.1619217250987;
 Fri, 23 Apr 2021 15:34:10 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Fri, 23 Apr 2021 15:34:00 -0700
Message-Id: <20210423223404.3860547-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.498.g6c1eba8ee3d-goog
Subject: [PATCH v3 0/4] KVM: x86: MSR_TSC_AUX fixes and improvements
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Reiji Watanabe <reijiw@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix potential cross-vendor landmines due to Intel and AMD having different
behavior for MSR_TSC_AUX[63:32], unify the logic across SVM and VMX, and
switch MSR_TSC_AUX via user return MSRs on SVM (the original goal).

v3:
  - Fix a comment typo. [Reiji]
  - Add patches to add missing guest_cpuid_has() check, drop bits 63:32 on
    AMD, and unify VMX and SVM emulation.
  - Rebase to kvm/next, commit c4f71901d53b ("Merge tag 'kvmarm-5.13' ... )

v2:
  - Rebase to kvm/queue (ish), commit 0e91d1992235 ("KVM: SVM: Allocate SEV
    command structures on local stack")
  - https://lkml.kernel.org/r/20210422001736.3255735-1-seanjc@google.com

v1: https://lkml.kernel.org/r/20210206003224.302728-1-seanjc@google.com


Sean Christopherson (4):
  KVM: SVM: Inject #GP on guest MSR_TSC_AUX accesses if RDTSCP
    unsupported
  KVM: SVM: Clear MSR_TSC_AUX[63:32] on write
  KVM: x86: Tie Intel and AMD behavior for MSR_TSC_AUX to guest CPU
    model
  KVM: SVM: Delay restoration of host MSR_TSC_AUX until return to
    userspace

 arch/x86/kvm/svm/svm.c | 58 +++++++++++++++++-------------------------
 arch/x86/kvm/svm/svm.h |  7 -----
 arch/x86/kvm/vmx/vmx.c | 13 ----------
 arch/x86/kvm/x86.c     | 34 +++++++++++++++++++++++++
 4 files changed, 58 insertions(+), 54 deletions(-)
```
#### [PATCH 00/12] Remove vfio_mdev.c, mdev_parent_ops and more
##### From: Jason Gunthorpe <jgg@nvidia.com>

```c
From patchwork Fri Apr 23 23:02:57 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Gunthorpe <jgg@nvidia.com>
X-Patchwork-Id: 12221961
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,MSGID_FROM_MTA_HEADER,
	SPF_HELO_NONE,SPF_PASS autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7D15AC433ED
	for <kvm@archiver.kernel.org>; Fri, 23 Apr 2021 23:03:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5DC2661477
	for <kvm@archiver.kernel.org>; Fri, 23 Apr 2021 23:03:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234465AbhDWXD4 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 23 Apr 2021 19:03:56 -0400
Received: from mail-mw2nam10on2084.outbound.protection.outlook.com
 ([40.107.94.84]:47680
        "EHLO NAM10-MW2-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S229718AbhDWXDv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 23 Apr 2021 19:03:51 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=AOMhoy2gq8WtOCOyFJTlsuR7zOUkCCyNSmh8vAM02CvDHeU+Sjsx/h00cShTAlO3AUTwhtCnhRouzZwC7Dr77XsXY9/FsMVPRsEB0LQGgDaKUayjj44qsQlf3GGRhI3TP3irfVD07U3sKu00JCxVbmDdWLaVOoygDSVA23DFOFj2AAh9SAoOISx13FZI5/9bigz/ELFa4WhpYsow46y29I2zBxUm/FQRMuih2xEffE9yEPhB87wK3o3bTfhIBr4/d4Kelha1ernbg9v8xmb0RvnxEOfX1Pb66cvkyKOqqOrWd1zhWNfuBV4mvoBQ0tarAzPMIxHjBWovgzy5Yq03ig==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=z1q3awXFXc0HeSJQj9cfvSiNE3+Z4I+19S3I6rAVhBo=;
 b=kiXXQCWDs5kipyWD/RlfyAR6iLmGiGH0l9ggAdYC5Qiu20r9wGN9MICgVx6Ud7mFOMVSVqTZcqe/4w5s6SyPzQlnVRoWRdGz9NAo9wYJz5rICIlgyDTx1WBlzcaPr4fXfevBwahqIEkdVJumDtvaKTY6yCfZlRydHxzT0xVpjro1c7IpYdiIYCwiz/We2AVS11UhblaW9bHjKGGf1+G1faW24Z40Z9XD82mFm5NaR640awvFj1E7n2Fu/BYGL0yiy2/AsqS55i1OCp31jfCS4T79fzuR3LPBGj26/g+aVRjGpAN5xKpRcM6kUAI8TAzMIlbAiMgUikcso7H6avYleQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=nvidia.com; dmarc=pass action=none header.from=nvidia.com;
 dkim=pass header.d=nvidia.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=Nvidia.com;
 s=selector2;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=z1q3awXFXc0HeSJQj9cfvSiNE3+Z4I+19S3I6rAVhBo=;
 b=rryBE0YBsAknoi2eLHS2ty7caZwCYRGSUZ0JxiTERxbCoFliZp4mGzc0v1p1zMNtcOLZfc1FAN9L93khOgBGC3ckgFsT7blH1UacwSIPCBA8ZxYdh6G19tgtYu0Xp6zmPpaC5Qrug7chj6Q2imG05lMKARpbPMMzZMto92ANEM81fjgxU+PdH/umHqxHCLXw8UhkOG0ZTr4VUS6GSWO+tSyFaiL6NlWvB8AWU48M50WwbXboPfBkU3GQ5yDTi133GjCi+7KgAyrhslT11FA/AkU8nzzSQ+/2e8pDDELqCs/YBYDNCv11Iyg/rPa/ig7nNRbSRj1SD9nGGEBgqDrmdA==
Authentication-Results: linux.intel.com; dkim=none (message not signed)
 header.d=none;linux.intel.com; dmarc=none action=none header.from=nvidia.com;
Received: from DM6PR12MB3834.namprd12.prod.outlook.com (2603:10b6:5:14a::12)
 by DM6PR12MB3513.namprd12.prod.outlook.com (2603:10b6:5:18a::21) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4042.24; Fri, 23 Apr
 2021 23:03:12 +0000
Received: from DM6PR12MB3834.namprd12.prod.outlook.com
 ([fe80::1c62:7fa3:617b:ab87]) by DM6PR12MB3834.namprd12.prod.outlook.com
 ([fe80::1c62:7fa3:617b:ab87%6]) with mapi id 15.20.4065.023; Fri, 23 Apr 2021
 23:03:12 +0000
From: Jason Gunthorpe <jgg@nvidia.com>
To: David Airlie <airlied@linux.ie>,
        Tony Krowiak <akrowiak@linux.ibm.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>,
        Daniel Vetter <daniel@ffwll.ch>,
        dri-devel@lists.freedesktop.org,
        Eric Farman <farman@linux.ibm.com>,
        Harald Freudenberger <freude@linux.ibm.com>,
        Vasily Gorbik <gor@linux.ibm.com>,
        Heiko Carstens <hca@linux.ibm.com>,
        intel-gfx@lists.freedesktop.org,
        intel-gvt-dev@lists.freedesktop.org,
        Jani Nikula <jani.nikula@linux.intel.com>,
        Joonas Lahtinen <joonas.lahtinen@linux.intel.com>,
        kvm@vger.kernel.org, Kirti Wankhede <kwankhede@nvidia.com>,
        linux-doc@vger.kernel.org, linux-s390@vger.kernel.org,
        Peter Oberparleiter <oberpar@linux.ibm.com>,
        Halil Pasic <pasic@linux.ibm.com>,
        Pierre Morel <pmorel@linux.ibm.com>,
        Rodrigo Vivi <rodrigo.vivi@intel.com>,
        Vineeth Vijayan <vneethv@linux.ibm.com>,
        Zhenyu Wang <zhenyuw@linux.intel.com>,
        Zhi Wang <zhi.a.wang@intel.com>
Cc: "Raj, Ashok" <ashok.raj@intel.com>,
        Dan Williams <dan.j.williams@intel.com>,
        Christoph Hellwig <hch@lst.de>,
        Leon Romanovsky <leonro@nvidia.com>,
        Max Gurtovoy <mgurtovoy@nvidia.com>,
        Tarun Gupta <targupta@nvidia.com>
Subject: [PATCH 00/12] Remove vfio_mdev.c, mdev_parent_ops and more
Date: Fri, 23 Apr 2021 20:02:57 -0300
Message-Id: <0-v1-d88406ed308e+418-vfio3_jgg@nvidia.com>
X-Originating-IP: [47.55.113.94]
X-ClientProxiedBy: MN2PR20CA0038.namprd20.prod.outlook.com
 (2603:10b6:208:235::7) To DM6PR12MB3834.namprd12.prod.outlook.com
 (2603:10b6:5:14a::12)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from mlx.ziepe.ca (47.55.113.94) by
 MN2PR20CA0038.namprd20.prod.outlook.com (2603:10b6:208:235::7) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4065.20 via Frontend
 Transport; Fri, 23 Apr 2021 23:03:11 +0000
Received: from jgg by mlx with local (Exim 4.94)        (envelope-from
 <jgg@nvidia.com>)        id 1la4pJ-00CHzN-Rw; Fri, 23 Apr 2021 20:03:09 -0300
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 7774210b-31c0-41e1-4257-08d906abf790
X-MS-TrafficTypeDiagnostic: DM6PR12MB3513:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR12MB3513B494B098716CEC38C557C2459@DM6PR12MB3513.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:9508;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 CSLfJq7bIZL7g+3+svOc/TY0JkF/CJriiUsnjUxFml7VfO335B3xyHN3D5y+hd+951US/DT//6fe8M4iAfUkRPIsIJuZoNLmZYYpzg6TbUeOTKvQ7UzRR2H/8BGM8G7rMoD9/e0ril7UdHUB0PrB+uizpirhkxMLv5lDI5T5nJ3i7ZxxOLWp29H3Wkdcth0DsWsYxKTypswiFgUQi2GVoBfD4LBPWjzw9v/AVGrasL4V7dBdoAMXigT7PlM9nHfYERLEyRkfb75RjyX8zN9RKL6vyvf693SiFe9/kr/hz44btwoSQNHKpklaDXfSrGyIXod9PAQsprYX75z3lxBU6rVj6jsn69m5PCwuPzOzyoAfr1oeYmIbFFeFaiK+V9Z5vBsu6q88WXXk9TNpiW7iC8nQ0+TjBsJL66YDfIGbTXoklJr6/QSTCCkKTNVWQ1aKwOxjMnvxuaGw3UqZbCWsmA4WsLfibHHeD+b1d4hJTJI0FzWeBtxQMNbZwhUfE0GsC+shqAkxI2UqWFqHHcHIaH3rTBE/YC8Xs/M1XQl9iu3a7o9TSJSiSz+X7W6xAi7DMZEYQZePcv+/LQfXgFgCwPSvQ/5TNHK0olcqyxtArGBwIDd5QETP9GNNk132fvXCSfnH+FS1PBJVWETWb/Z/CVqqFA2LDOC9Cws0I4ixVNPenjGNoaBrpWo4zR+6pQoerpWeMxEDlZbD7mcwDIQX5C2gmaOv8wy0rnZRVZ8QALs=
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR12MB3834.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(376002)(396003)(39860400002)(366004)(346002)(136003)(36756003)(66556008)(26005)(66476007)(107886003)(426003)(8936002)(966005)(83380400001)(921005)(9786002)(5660300002)(186003)(86362001)(9746002)(54906003)(38100700002)(2616005)(316002)(8676002)(7416002)(2906002)(4326008)(110136005)(66946007)(6666004)(478600001)(4216001);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 3bFOkOrgZ+c/Lp3YoTuVQVOWSrD4qcxMxSg6xhR/FD6fLF57kx2Dv3aATirjy9Zh2oV7VKG1l5igwiXGEvQklQ5J5JbY6S7vWnUU/ftsk4IKVXr5BUWS0iNbFdgCHdfHSpYJLSPSs6UqvEaqsgWhGZAwkitsfm6hmQMxve6LfCpc6p2KYhaASWiLdrAvqv9YtXPmrdYIRBH86NDDFVgtzxHuUK+0D0bd9dUXv3qtMM/JiB1FJdhfE+kltlph39vpbsRAnCh28a8w/q844Vw/43meXng1eX5Mihci6e2W6zeKsjBTxgCVv9XFQElT8WwdAdvLQlC527DpOTUfu3vdolx4gtvi6DGJ4NGjIjqbvVjoUz3KDCVFGTL45Rqql1Rbsz5pi85NcpgeCwjqOLtiERUUL06ix5/Fkxf/aPc/SJ+8zKGQIli7rxqY7bHct+X/T5bsqCuQ3wnB/hctPPIzTS/sMROHEwGfbQNg+cOELIoWL+eigu8AVTO10IrZ2oZdM4kZX1kvNec+jIrYh5EtUcF+r3xpMaW2XlED/pagV7sjz8n4aI0pxZ+zLCzCkosg/9gnLZyt4aJ3FiPkIRKAeuW78aRRxSpy55UNpy+Ip2Pvfw3lrf8iUP4J9z3bVHZrg7XJqIgLjfGgEEtpjdBfaM4MkwPpW/8vD/XgKhAUTBpggfZFjPLrBo+Re1OhxAEzTMEXd8UHRjMCSw6APf82b9EQtpEkJl7u3kg80jr5LV5/B4FwQVS43PRkDH0JuxaRvztB4PNtGT0CaPfQL2bb+befNJbOQamdRLttoYR0dZVJsCwCJHgcStf77Kx0HI2RKlaoewSOnwkFOOgQ8iuAM/sca/d5xDOJbfA2jQQA709r+Tk4hXTTsld04CdBuFnsNMUfnTKIJPHwt/Qpq959lzhyRROtbx46uEhUzfcN11rPJa06+KGrGoxdlOV+lsz523dpgrT231uHHI+9qJXmgyFc5ePtbu+EP6Y0a66XP6gtoTuKgOXH1YTYFcbfT4F5pZXBokLX/oXnABER0Ur27PizHClKxaArkr53BLM6bXVRVr4Jrpz+eItjY83+6B7dPY38vPS61+4sXrWFkGHfeTB0ihtkE91div0g/qvTcbY394MXN38Qxa7qX6Yj0fRGyTnZUMS4ds58Bc7SXRTkWaQVA5aY0waAwxw6Hv+MWfXkWC95IHIZol8G2yWDRn54rvEhJbjl/ihG6l1dRDMDN6lYeQD7I6PsYUHScnI/IXRRcULxYMZivWn5xhY+jwLzxoKmdmD5yujXtO5OCefHSZwo+zRPnYdzKwhSoJg6fSokRDvQ85U0mXT9iP7VdNcG
X-OriginatorOrg: Nvidia.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 7774210b-31c0-41e1-4257-08d906abf790
X-MS-Exchange-CrossTenant-AuthSource: DM6PR12MB3834.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 23 Apr 2021 23:03:11.4495
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 43083d15-7273-40c1-b7db-39efd9ccc17a
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 1fWxThH7+xEaCydsLn94c3kkVX/a4Obk8XAlqIeijjfyspcrcyut3JLiEafCo2R2
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR12MB3513
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Prologue
========

This is series #3 in part of a larger work that arose from the minor
remark that the mdev_parent_ops indirection shim is useless and
complicates things.

It applies on top of Alex's current tree and requires the prior two
series.

This series achieves the removal of vfio_mdev.c. The future patches are all
focused on leveraging the changes made in the prior series to simplify the
API and device operation.

A preview of the future series's is here:
  https://github.com/jgunthorpe/linux/pull/3/commits

========

The mdev bus's core part for managing the lifecycle of devices is mostly
as one would expect for a driver core bus subsystem.

However instead of having a normal 'struct device_driver' and binding the
actual mdev drivers through the standard driver core mechanisms it open
codes this with the struct mdev_parent_ops and provides a single driver
that shims between the VFIO core and the actual device driver.

Make every one of the mdev drivers implement an actual struct mdev_driver
and directly call vfio_register_group_dev() in the probe() function for
the mdev.

Squash what is left of the mdev_parent_ops into the mdev_driver and remap
create(), remove() and mdev_attr_groups to their driver core
equivalents. Arrange to bind the created mdev_device to the mdev_driver
that is provided by the end driver.

The actual execution flow doesn't change much, eg what was
parent_ops->create is now device_driver->probe and it is called at almost
the exact same time - except under the normal control of the driver core.

This allows deleting the entire mdev_drvdata, and tidying some of the
sysfs. Many places in the drivers start using container_of()

This cleanly splits the mdev sysfs GUID lifecycle management stuff from
the vfio_device implementation part, the only VFIO special part of mdev
that remains is the mdev specific iommu intervention.

Thanks,
Jason

Jason Gunthorpe (12):
  vfio/mdev: Remove CONFIG_VFIO_MDEV_DEVICE
  vfio/mdev: Allow the mdev_parent_ops to specify the device driver to
    bind
  vfio/mtty: Convert to use vfio_register_group_dev()
  vfio/mdpy: Convert to use vfio_register_group_dev()
  vfio/mbochs: Convert to use vfio_register_group_dev()
  vfio/ap_ops: Convert to use vfio_register_group_dev()
  vfio/ccw: Convert to use vfio_register_group_dev()
  vfio/gvt: Convert to use vfio_register_group_dev()
  vfio/mdev: Remove mdev_parent_ops dev_attr_groups
  vfio/mdev: Remove mdev_parent_ops
  vfio/mdev: Use the driver core to create the 'remove' file
  vfio/mdev: Remove mdev drvdata

 .../driver-api/vfio-mediated-device.rst       |  55 ++---
 Documentation/s390/vfio-ap.rst                |   1 -
 arch/s390/Kconfig                             |   2 +-
 drivers/gpu/drm/i915/Kconfig                  |   2 +-
 drivers/gpu/drm/i915/gvt/kvmgt.c              | 210 +++++++++--------
 drivers/s390/cio/vfio_ccw_drv.c               |  21 +-
 drivers/s390/cio/vfio_ccw_ops.c               | 136 ++++++-----
 drivers/s390/cio/vfio_ccw_private.h           |   5 +
 drivers/s390/crypto/vfio_ap_ops.c             | 138 ++++++-----
 drivers/s390/crypto/vfio_ap_private.h         |   2 +
 drivers/vfio/mdev/Kconfig                     |   7 -
 drivers/vfio/mdev/Makefile                    |   1 -
 drivers/vfio/mdev/mdev_core.c                 |  65 ++++--
 drivers/vfio/mdev/mdev_driver.c               |  10 +-
 drivers/vfio/mdev/mdev_private.h              |   4 +-
 drivers/vfio/mdev/mdev_sysfs.c                |  37 ++-
 drivers/vfio/mdev/vfio_mdev.c                 | 180 ---------------
 drivers/vfio/vfio.c                           |   6 +-
 include/linux/mdev.h                          |  86 +------
 include/linux/vfio.h                          |   4 +
 samples/Kconfig                               |   6 +-
 samples/vfio-mdev/mbochs.c                    | 166 +++++++------
 samples/vfio-mdev/mdpy.c                      | 162 +++++++------
 samples/vfio-mdev/mtty.c                      | 218 +++++++-----------
 24 files changed, 649 insertions(+), 875 deletions(-)
 delete mode 100644 drivers/vfio/mdev/vfio_mdev.c
```
