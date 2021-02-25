#### [GIT PULL] VFIO updates for v5.12-rc1
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 12102189
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-20.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,
	SPF_HELO_NONE,SPF_PASS autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D518FC433DB
	for <kvm@archiver.kernel.org>; Wed, 24 Feb 2021 17:52:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8FB4A64EDD
	for <kvm@archiver.kernel.org>; Wed, 24 Feb 2021 17:52:32 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234644AbhBXRwD (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 24 Feb 2021 12:52:03 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:58174 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S234202AbhBXRvu (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 24 Feb 2021 12:51:50 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1614189018;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=X9cy0F4zcJr85qheHgGEfaSe+Yv6NngaYwEOKPQ/d5U=;
        b=VrPGu/6vKGF8jSgsnW9cy6rj8iVT/K7Hi/kfgdP0aQi6nmeg97qlj0CdYaBmMAxFBPvVA/
        99HIRkGyLlIYTkuI8RbewtV2gzFsUQBvErPkNcdYoIwocGcRb0Rgb/7p/lffZlsMiF0yZy
        9244hkzW6ukQVCBxYnk893omae66xOU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-509-w0kKXsMvP2ujtHkiVK0RtA-1; Wed, 24 Feb 2021 12:50:15 -0500
X-MC-Unique: w0kKXsMvP2ujtHkiVK0RtA-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id D58FF180E469;
        Wed, 24 Feb 2021 17:50:13 +0000 (UTC)
Received: from omen.home.shazbot.org (ovpn-112-255.phx2.redhat.com
 [10.3.112.255])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 9E58110016F0;
        Wed, 24 Feb 2021 17:50:13 +0000 (UTC)
Date: Wed, 24 Feb 2021 10:50:13 -0700
From: Alex Williamson <alex.williamson@redhat.com>
To: Linus Torvalds <torvalds@linux-foundation.org>
Cc: <linux-kernel@vger.kernel.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>
Subject: [GIT PULL] VFIO updates for v5.12-rc1
Message-ID: <20210224105013.03713eb6@omen.home.shazbot.org>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Linus,

The following changes since commit 3e10585335b7967326ca7b4118cada0d2d00a2ab:

  Merge tag 'for-linus' of git://git.kernel.org/pub/scm/virt/kvm/kvm (2021-02-21 13:31:43 -0800)

are available in the Git repository at:

  git://github.com/awilliam/linux-vfio.git tags/vfio-v5.12-rc1

for you to fetch changes up to 4d83de6da265cd84e74c19d876055fa5f261cde4:

  vfio/type1: Batch page pinning (2021-02-22 16:30:47 -0700)

----------------------------------------------------------------
VFIO updates for v5.12-rc1

 - Virtual address update handling (Steve Sistare)

 - s390/zpci fixes and cleanups (Max Gurtovoy)

 - Fixes for dirty bitmap handling, non-mdev page pinning,
   and improved pinned dirty scope tracking (Keqian Zhu)

 - Batched page pinning enhancement (Daniel Jordan)

 - Page access permission fix (Alex Williamson)

----------------------------------------------------------------
Alex Williamson (3):
      Merge branch 'v5.12/vfio/next-vaddr' into v5.12/vfio/next
      Merge commit '3e10585335b7967326ca7b4118cada0d2d00a2ab' into v5.12/vfio/next
      vfio/type1: Use follow_pte()

Daniel Jordan (3):
      vfio/type1: Change success value of vaddr_get_pfn()
      vfio/type1: Prepare for batched pinning with struct vfio_batch
      vfio/type1: Batch page pinning

Heiner Kallweit (1):
      vfio/pci: Fix handling of pci use accessor return codes

Keqian Zhu (3):
      vfio/iommu_type1: Populate full dirty when detach non-pinned group
      vfio/iommu_type1: Fix some sanity checks in detach group
      vfio/iommu_type1: Mantain a counter for non_pinned_groups

Max Gurtovoy (3):
      vfio-pci/zdev: remove unused vdev argument
      vfio-pci/zdev: fix possible segmentation fault issue
      vfio/pci: remove CONFIG_VFIO_PCI_ZDEV from Kconfig

Steve Sistare (9):
      vfio: option to unmap all
      vfio/type1: unmap cleanup
      vfio/type1: implement unmap all
      vfio: interfaces to update vaddr
      vfio/type1: massage unmap iteration
      vfio/type1: implement interfaces to update vaddr
      vfio: iommu driver notify callback
      vfio/type1: implement notify callback
      vfio/type1: block on invalid vaddr

Tian Tao (1):
      vfio/iommu_type1: Fix duplicate included kthread.h

 drivers/vfio/pci/Kconfig            |  12 -
 drivers/vfio/pci/Makefile           |   2 +-
 drivers/vfio/pci/vfio_pci.c         |  12 +-
 drivers/vfio/pci/vfio_pci_igd.c     |  10 +-
 drivers/vfio/pci/vfio_pci_private.h |   2 +-
 drivers/vfio/pci/vfio_pci_zdev.c    |  24 +-
 drivers/vfio/vfio.c                 |   5 +
 drivers/vfio/vfio_iommu_type1.c     | 564 ++++++++++++++++++++++++++----------
 include/linux/vfio.h                |   7 +
 include/uapi/linux/vfio.h           |  27 ++
 10 files changed, 475 insertions(+), 190 deletions(-)
```
#### [PATCH] KVM: SVM: Fix nested VM-Exit on #GP interception handlingFrom: Sean Christopherson <seanjc@google.com>
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12101155
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2DB26C433DB
	for <kvm@archiver.kernel.org>; Wed, 24 Feb 2021 01:19:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D99DC64E6B
	for <kvm@archiver.kernel.org>; Wed, 24 Feb 2021 01:19:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234312AbhBXBTN (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 23 Feb 2021 20:19:13 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:52830 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S234357AbhBXBFL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 23 Feb 2021 20:05:11 -0500
Received: from mail-qt1-x849.google.com (mail-qt1-x849.google.com
 [IPv6:2607:f8b0:4864:20::849])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id AF38BC06178A
        for <kvm@vger.kernel.org>; Tue, 23 Feb 2021 16:56:31 -0800 (PST)
Received: by mail-qt1-x849.google.com with SMTP id l1so482650qtv.2
        for <kvm@vger.kernel.org>; Tue, 23 Feb 2021 16:56:31 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=qPqWTKGBtiXgew3PhU0N/4Jj0Q0xiKY6q8BL4BwzsAU=;
        b=HunJVjKbKYQ5+XtdKimDZXAv30Guhr4IP7oIEdJc7r2ZY8T9q1TUL/oYbgxHvoizNY
         vVaw1gzKdcN61vKj+zzI4R6vjvUWlc4kq/PEuq24S22oLK7OYKNTlTgvh69hULpZaCWp
         9hi14vlflVmxyWK+peWu78muWleYnJ1efDkxVY24A2Y+eqvqUrh30D4+Q0Js1dhFb88s
         RLeWbzv0rw2i1wKgwjrZrP+ZN66NbrV+4HBSLGivZ1JM0ZFlwv4RVFR+Z3FxQJcVkgJD
         Fqa+4OPHLFDG4RCmRqcpmDHSNxWXq5XaVW5+tqrhUlWI7jp40/Xw9/bA4sOYc4+JAat6
         2f2Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:message-id:mime-version
         :subject:from:to:cc;
        bh=qPqWTKGBtiXgew3PhU0N/4Jj0Q0xiKY6q8BL4BwzsAU=;
        b=fgWY+ULTMuhH0d0cpKzToz4jdTNdUCtD5GNih/3avgOoRPTX+/f7T7u+exCwseBU3L
         3v/LnX4PawvlsutYmDnW3Dnwkc1R/86Hzrgw9VgqojHQHskpR6eEn9tmGqkylQihHpaD
         d+CO/xG9e8u7+lhZO2db4Xt//g1yZQw8Y8W6eT2NXPdYV3Tk78EUtT4sLi+g5Guk8b0h
         qFxiWWsD/qCvqVf+FG9zQq+BksZuogT06sFeCOHWJqhREslYZ1HlLEoAPX7+oxwCZ2HO
         C8fdt+cSsccuXxaSaL2BQZCVrGOK651/Yu1rIs+5nHzoq1472GFZDAFdGAwtq89QksJ9
         KKPQ==
X-Gm-Message-State: AOAM530BQ+uAmzXu105KL93leUxLd+QCtyzM713Zea8HWeuqlrcXWQSS
        bxLmE120E/NE7yl+NxYZlPLuPoMRTiQ=
X-Google-Smtp-Source: 
 ABdhPJzH3hAGs0FwoUemhwbym6SDVcEwG16rcuwMXwz97fmv4n8V/0SYC1Yl3E1PbNjpcyLrGYK8r924QTg=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:385f:4012:d20f:26b5])
 (user=seanjc job=sendgmr) by 2002:a05:6214:cad:: with SMTP id
 s13mr27824910qvs.53.1614128190725; Tue, 23 Feb 2021 16:56:30 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Tue, 23 Feb 2021 16:56:26 -0800
Message-Id: <20210224005627.657028-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.0.617.g56c4b15f3c-goog
Subject: [PATCH] KVM: SVM: Fix nested VM-Exit on #GP interception handling
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

Fix the interpreation of nested_svm_vmexit()'s return value when
synthesizing a nested VM-Exit after intercepting an SVM instruction while
L2 was running.  The helper returns '0' on success, whereas a return
value of '0' in the exit handler path means "exit to userspace".  The
incorrect return value causes KVM to exit to userspace without filling
the run state, e.g. QEMU logs "KVM: unknown exit, hardware reason 0".

Fixes: 14c2bf81fcd2 ("KVM: SVM: Fix #GP handling for doubly-nested virtualization")
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/kvm/svm/svm.c | 7 ++++++-
 1 file changed, 6 insertions(+), 1 deletion(-)

```
#### [PATCH v3 1/5] KVM: x86: dump_vmcs should not assume GUEST_IA32_EFER is valid
##### From: David Edmondson <david.edmondson@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Edmondson <david.edmondson@oracle.com>
X-Patchwork-Id: 12101905
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,UNPARSEABLE_RELAY,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 09ED7C433E0
	for <kvm@archiver.kernel.org>; Wed, 24 Feb 2021 14:17:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id ACA8F64E6B
	for <kvm@archiver.kernel.org>; Wed, 24 Feb 2021 14:17:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235213AbhBXOMS (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 24 Feb 2021 09:12:18 -0500
Received: from aserp2130.oracle.com ([141.146.126.79]:37708 "EHLO
        aserp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S234883AbhBXNcH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 24 Feb 2021 08:32:07 -0500
Received: from pps.filterd (aserp2130.oracle.com [127.0.0.1])
        by aserp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 11ODTLcW160530;
        Wed, 24 Feb 2021 13:29:30 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references :
 content-transfer-encoding : content-type : mime-version;
 s=corp-2020-01-29; bh=Xpw/yhtG2V6Muoah1BF32QpLvcA/5dBWSpMW/TK0kEI=;
 b=sklgfuWNUDN7lOpUiWYoCJ//Kk4khmFhb78EEKdSEHgZhH95xItW6uTg7cV+9adJcuF9
 EoVACEj+EkKGEiYWIATM1ZpB03XY9aXyD4ER1LJK1KPdgETknexmt6DFrvwTJkqJM8u/
 gf8aaTlppY/70H+uRLRrRBjgx9QsWPK1CfjzFgxc+LMUykij2JtIG2L1C8CVFAet7Jw1
 6aAmg37YwNOE5sh/I1EHZSvSy33b+CohPNePGNOFuAvPvA1Jm5PQWzrXDz+IQj08JpA8
 bPKu71tgEZLcUgjthmDw5FFEMQEenI5N9qISW0IKJ5V2AFpbfMmdIaNKzLi6asRL8qg5 dg==
Received: from userp3020.oracle.com (userp3020.oracle.com [156.151.31.79])
        by aserp2130.oracle.com with ESMTP id 36vr6258dt-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 24 Feb 2021 13:29:30 +0000
Received: from pps.filterd (userp3020.oracle.com [127.0.0.1])
        by userp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 11ODQBqj184325;
        Wed, 24 Feb 2021 13:29:29 GMT
Received: from nam12-dm6-obe.outbound.protection.outlook.com
 (mail-dm6nam12lp2176.outbound.protection.outlook.com [104.47.59.176])
        by userp3020.oracle.com with ESMTP id 36uc6t4rmp-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 24 Feb 2021 13:29:29 +0000
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=jnF+fLi51TBoEKapOlVesNwbk6nCyEdjxOUfkD+bWw02N+0ylHmOXrnNCQ4vq62naULIlMrmjDY/5k3Qjyeyt5JrqKat2FMUBYHc5We5vSI31jypB/dLL3ZDLwFJbEqLXL3eLpjhVXr88n9yr2NVgzf7l+/fUKokqdVnZ5SWrC0aPhGHi/Mq9xDdohoQQfSSR8vlK7oV6RAe10TjPfHEqY/VAkaLDLZCo/CV434vi8Cnxv8UZJHFXt9KRRbEZz6yxblF5hb0wr4ybC9GuCaYHjrbfhq5yXEe1ccgLOHmr6I9lFxQt/zyrC//sgt1G1SMTr1Mn9C175I+ev4KtBlfTg==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=Xpw/yhtG2V6Muoah1BF32QpLvcA/5dBWSpMW/TK0kEI=;
 b=lFcTWx2IhyfUJqHiNKKo4IiMidJCJOwliLQhBxx4EMbrXnxTjHqMoApVbYSmWLFOFJK9MdL76/lTWjSN3Q38MvBjBLvcYRGwH1uRxXJeYbLFkbVhP9nIsMa9F2zs9qBRJisH72PDCSMTt4DU0dbDaLJ+UKZQ4FAGLH8ivgaCxE476SqLBL6cc7OfOY7iMs12gCtN0EH/NUwJXeeptcJpfj5xrb8tN4Oosh7ilLo5cssCscTIJ2giLnRhcm6iY8/beLmkKzfkUP+bCdz3pMSklwvOXV4GbVO1lbh7O7h4zSAMW2kIN86lplkzNpPYogpihn19KBTvmLIcqqWWhYiU9g==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=oracle.com; dmarc=pass action=none header.from=oracle.com;
 dkim=pass header.d=oracle.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=oracle.onmicrosoft.com; s=selector2-oracle-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=Xpw/yhtG2V6Muoah1BF32QpLvcA/5dBWSpMW/TK0kEI=;
 b=XpGuBh4sMehdncqAyXB9Wjdr2DqnRgacKPVW9dN3EYpvmM6JqgwvKMmpRKZyBBTFbCkk/YM1/wNmEDsTnE4oVAni04scz1t1pb0JaUuRnf9QuC7ySYCQ5v2vVe0dCE/ZCDTX66+YyIK+Pd/zQAwL7SWGcA0QDrdSu22ZQyHQh/E=
Authentication-Results: redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=none action=none header.from=oracle.com;
Received: from DM6PR10MB3148.namprd10.prod.outlook.com (2603:10b6:5:1a4::21)
 by DM6PR10MB3146.namprd10.prod.outlook.com (2603:10b6:5:1a6::14) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3868.32; Wed, 24 Feb
 2021 13:29:27 +0000
Received: from DM6PR10MB3148.namprd10.prod.outlook.com
 ([fe80::f871:5965:2081:3934]) by DM6PR10MB3148.namprd10.prod.outlook.com
 ([fe80::f871:5965:2081:3934%5]) with mapi id 15.20.3868.033; Wed, 24 Feb 2021
 13:29:27 +0000
From: David Edmondson <david.edmondson@oracle.com>
To: linux-kernel@vger.kernel.org
Cc: Borislav Petkov <bp@alien8.de>, x86@kernel.org,
        Jim Mattson <jmattson@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Sean Christopherson <seanjc@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        "H. Peter Anvin" <hpa@zytor.com>, kvm@vger.kernel.org,
        Paolo Bonzini <pbonzini@redhat.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>,
        David Edmondson <david.edmondson@oracle.com>
Subject: [PATCH v3 1/5] KVM: x86: dump_vmcs should not assume GUEST_IA32_EFER
 is valid
Date: Wed, 24 Feb 2021 13:29:15 +0000
Message-Id: <20210224132919.2467444-2-david.edmondson@oracle.com>
X-Mailer: git-send-email 2.30.0
In-Reply-To: <20210224132919.2467444-1-david.edmondson@oracle.com>
References: <20210224132919.2467444-1-david.edmondson@oracle.com>
X-Originating-IP: [2001:8b0:bb71:7140:64::1]
X-ClientProxiedBy: LO2P265CA0484.GBRP265.PROD.OUTLOOK.COM
 (2603:10a6:600:13a::9) To DM6PR10MB3148.namprd10.prod.outlook.com
 (2603:10b6:5:1a4::21)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from disaster-area.hh.sledj.net (2001:8b0:bb71:7140:64::1) by
 LO2P265CA0484.GBRP265.PROD.OUTLOOK.COM (2603:10a6:600:13a::9) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3890.19 via Frontend
 Transport; Wed, 24 Feb 2021 13:29:24 +0000
Received: from localhost (disaster-area.hh.sledj.net [local])   by
 disaster-area.hh.sledj.net (OpenSMTPD) with ESMTPA id 9bdc4505;
      Wed, 24 Feb 2021 13:29:19 +0000 (UTC)
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: fcfa492c-10b7-4952-db36-08d8d8c8349a
X-MS-TrafficTypeDiagnostic: DM6PR10MB3146:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR10MB3146C5C3C130B087C8856DFA889F9@DM6PR10MB3146.namprd10.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:6790;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 021S6outwtCODseOjVexkfWdLsM/0JosKN/oVAsaqyshcGzlE95i2+e6oqxI2G8TKzsMod/dV+kHG9f3xIoKawWji99Tl5oI/ad8toVcrlrtPU4yvKyYOaNPYce1IDWsr0OFv7WZYI/BQTeWdSOEAZegTC/hBH8JDW4y/6fyU4JvuBb0DaZ48wPRYhYLph1k4ATDlDPYrf3lBt0GoUuBwVSuPtUZHRWU+BkSpAL6k+vqAO52+xkFudUxtQQlC+AcmhmhINk3Wndd4Oy227158eUU8Dw6vvNPg++K+Jsi7MJUIoEjFz0/cb9pnD1J4dNDfEc9eZ4fcOypG78tD9xz62uBCTk6U6YoomeMMuI2t7ytba53QN5g2mN0khBYUq70sJvWv3/pmccKHkCx5jPHWKwi4LcSgLD7N6xVQlo/ViSruFi9zQ097M4i8zCVplCSTNwZWc5wvrBfsUyTW4dvAS9uEjyyHIX3kpXD32VKbmSGUTkyjyapnmaaFo9DFb3ve34YiVlRFGJwX03coySvdA==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR10MB3148.namprd10.prod.outlook.com;PTR:;CAT:NONE;SFS:(136003)(346002)(376002)(39860400002)(396003)(366004)(107886003)(2906002)(44832011)(6916009)(4326008)(6666004)(86362001)(478600001)(8936002)(2616005)(316002)(7416002)(54906003)(36756003)(83380400001)(186003)(66476007)(66946007)(52116002)(1076003)(8676002)(66556008)(5660300002);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 sAZETCU/ZXAAmdPX2XXh1FbES28HjFlqt/fkb7Dx4Sty+54zaLCflGStr+0YJKDWUAZls3OgGdz7HflqPFckdi+af+zWJwbfaVxUWoyXI3Chrkz8XpGraBIuZnKkgVIMDcUFrFBzAxrCgkEamJbLhtk9kTErqCsTTy2fa6InSZio/zX6jMVIX57apQbPX1+t8m+MQBY2yxuyRbm1ueU8a4nHLCjN2rMbDmcT27Q5p/g73uz0WYyeXMGqoVt1H5nt6/ptqwpX8CDOrI9v3qEMhTFJEOEw+lA1SbP5IWSC8gjMeZNje2js4wsxP1RLcIZc6W0JVwZ4rHDZ0kjrBrNwMgKMaXQTHktVYBx0iLk7r9vNY9XzWnHqwB4brGBFhuYdPOqjP/x97hNWm8PJuj/oJmVXHolQdS8ejbeYAnbaCc39DiM3HCpQtrcMT+Nq9ydg/BIZMB258EoB4hJU0eMUsAfq0ucsZbtNjiiVx7xcDKb4ibOxjpIxrQlA4IQD04iq0I0BeW0LizJy6V8MkbXxVHKfG4cDAvtS9CCLI/jZm24tfu9IDDzYIzcmWj3c7+yqZI/EUIp2FeoGcaycaO8iF9rz5od8eL8XE4BOacUkK1Dc3K9DDZd0mJ887gOr8KfIEq3j9roAaCHdFejKliI8EH9DKdqW+MktNFqDXhw68NliXodt4gQE87sh0pBdOW/oY06KFnzWE5/F8tlRYnUvBEMa18o8F22qOcBsT8fF03S5a+TRvg7DKRUPrpvFVz8poFfljlE3A0qD8AJWuFHYSsIDj6OP5WFrVYKGNtasuS8JP/saQm02Cfgb2YbU8Xxg/HsHNKaB8ADmqUNt6DYmtMQuf8bituumt+h792Y2QlJLCbvwDbb9mdlITAv27watrjvuWD9O+ekprcSbI9aN6zhkX/g6PHQsBEL2Ym5+4g6ADExf2EnYKUsrC10GQIoKzDfRyHHN203xNFLf9PSp5G6j5YBRxrneXDWQMo3jw8AyfeHbKXYa1YDq2tujhOrybuSSye5tadtLPPojwzhv4b/9bkacdGGO1kyjO/bvVWNE7Hv2i1Jk3rzLT18TOlrCaGVc9JajD1LFQAP0doh1le5DZsKVHi4AIY8zOz7e+gB6rr9LnfP4uA8TbyU/a3XnwNPYdqGxlugl7RLUnisrv3YguQRdKjjtadLEmSYxfvgDn0RdY8lU/7P1S++KAiWXXmHrmaYuFrjnABJ/iDIlyuAAWxgxWcpT8aR4iuBcR6KVWtR/Yddeeaf2baXoMpXktCrgNbD5+saOPsyzwIMhnESVWTECu+OYayLos6MiVR8WoPKnlyF67C6Hv4QVbOuOWvHlXnLYQkn787oNZ9RqHQ==
X-OriginatorOrg: oracle.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 fcfa492c-10b7-4952-db36-08d8d8c8349a
X-MS-Exchange-CrossTenant-AuthSource: DM6PR10MB3148.namprd10.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 24 Feb 2021 13:29:26.7064
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 4e2c6054-71cb-48f1-bd6c-3a9705aca71b
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 sNnmQJjGR8G5IQlOYBWQq86q5J4+Uzmhnw0LBOZ4POtaEfD7JRZiPVhddkbNPkv/YcAmgeXQmTAj60pXjGxjry/IOUtxz5wO7fd2nxLORs8=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR10MB3146
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9904
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=0
 mlxscore=0 spamscore=0
 mlxlogscore=966 adultscore=0 bulkscore=0 malwarescore=0 phishscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2102240104
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9904
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=0
 bulkscore=0
 clxscore=1015 mlxlogscore=999 lowpriorityscore=0 phishscore=0
 impostorscore=0 adultscore=0 mlxscore=0 priorityscore=1501 malwarescore=0
 spamscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102240105
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If the VM entry/exit controls for loading/saving MSR_EFER are either
not available (an older processor or explicitly disabled) or not
used (host and guest values are the same), reading GUEST_IA32_EFER
from the VMCS returns an inaccurate value.

Because of this, in dump_vmcs() don't use GUEST_IA32_EFER to decide
whether to print the PDPTRs - always do so if the fields exist.

Fixes: 4eb64dce8d0a ("KVM: x86: dump VMCS on invalid entry")
Signed-off-by: David Edmondson <david.edmondson@oracle.com>

if valid
---
 arch/x86/kvm/vmx/vmx.c | 9 +++------
 1 file changed, 3 insertions(+), 6 deletions(-)

```
#### [PATCH v4 1/5] KVM: x86: dump_vmcs should not assume GUEST_IA32_EFER is valid
##### From: David Edmondson <david.edmondson@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Edmondson <david.edmondson@oracle.com>
X-Patchwork-Id: 12101917
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,UNPARSEABLE_RELAY,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 89CEEC4332B
	for <kvm@archiver.kernel.org>; Wed, 24 Feb 2021 14:17:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6678364F00
	for <kvm@archiver.kernel.org>; Wed, 24 Feb 2021 14:17:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235856AbhBXOOW (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 24 Feb 2021 09:14:22 -0500
Received: from aserp2130.oracle.com ([141.146.126.79]:59044 "EHLO
        aserp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232350AbhBXOHm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 24 Feb 2021 09:07:42 -0500
Received: from pps.filterd (aserp2130.oracle.com [127.0.0.1])
        by aserp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 11OE58LJ018083;
        Wed, 24 Feb 2021 14:05:08 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references :
 content-transfer-encoding : content-type : mime-version;
 s=corp-2020-01-29; bh=Xpw/yhtG2V6Muoah1BF32QpLvcA/5dBWSpMW/TK0kEI=;
 b=Qy8goXnXpwmkDO/g1ftNVb+TGB7BN7t1Etb00bjnc3LgDJ3oa86DOWn1JhJDfmYh0NMj
 jhWE+jkVImW02b/uhUFdQPJkkobbfC24OxWWjz9dXylnx8uEqoimX4U0w0/6+q7w90MM
 NlSfzG8f0hBNtu8NOq73RhztxbgJnZ3eUDWLOiNjBwtNxm6yQ429Ekj9koPZGcmAh8/+
 R6cwuZtNCWYHbA3/5S9Jnob9o5furr8C38+EcK1mpwzPYppPoCZyE6zwGP7ZGBkm29Ti
 9lWiSIo5J8/Jig5SbwIDDxERvSoAC+s2YJQpQFsk4XOu4sZDinPgEXnOY5gk/Be80Et+ lQ==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by aserp2130.oracle.com with ESMTP id 36vr625bwv-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 24 Feb 2021 14:05:08 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 11ODscsj012587;
        Wed, 24 Feb 2021 14:05:08 GMT
Received: from nam11-co1-obe.outbound.protection.outlook.com
 (mail-co1nam11lp2170.outbound.protection.outlook.com [104.47.56.170])
        by aserp3020.oracle.com with ESMTP id 36ucb0sbe5-2
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 24 Feb 2021 14:05:08 +0000
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=OOzk64z8SrG7SQ1YHK7yLQmvixHuWg2MX5Hgv94QkRkqi1Z5IsIuU0R8vDONujatmhzT+unFj9ugjSs3eomAVnX7RiNpQXaqUI5Dph8RiGFO/GpusOs6AB4pAXqfES+/PLYJCjh0jSGgmKfB/HWsK8r5Ht2M0430+loOqav3nZKnLhf6lAHAXDTukvqlsyeciqTcSkb1ziQs8Dcl+MWe9q/KKqgpeArkMCk2ansAa9n90lMrOPuDWDKC5MZ70hQhzCVc18eLV/UpS7JWWn42QWfSakINoluTQibzJ+8Vv0TxwMwBex62cB7IQYV2d+2hk33Z6+yMYntvUg0mabTDIA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=Xpw/yhtG2V6Muoah1BF32QpLvcA/5dBWSpMW/TK0kEI=;
 b=jqgFH9w5lBfZiGrexmMAOvLSimaF6PS10El8bHw+Tc2F/HotOMYqnYIDKP8njWKA1BN+o+VyFJv5kJw2V/xdZDcg3MjfdKXbbd+EavGE6w7Y5GzciSRNOVohJXxMqJf2r+9egkoge0jcjH9e4C3AmurUDREx4TfJLlEBURbEwxTNfoU7vMDbGqu1NgjtAZ3hL2SI3O+plbaPDUHQgf/8Pt7yvzFFHyb7URKJOp2TuI8ca1URG7CVFE7yNI+j+6OGUoaeL1yROzHvqpDultZENSEHrvtZjrUEvnbSGAJx8HOgU9tee3kvYheCUeIBIUigOxIsJ5MpJpTvRavQO4npoA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=oracle.com; dmarc=pass action=none header.from=oracle.com;
 dkim=pass header.d=oracle.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=oracle.onmicrosoft.com; s=selector2-oracle-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=Xpw/yhtG2V6Muoah1BF32QpLvcA/5dBWSpMW/TK0kEI=;
 b=sEnJOI6JltvaFvmr/YKPcIABeHGRSVXb6Jcn9XYYAvIF+5NpmbOXuuD3Iai4jBbzqROqf+U76fxBB8zmXqcXenDB80iTEDgmaceHcilwac69IX/dCL/xtiD4307hn7bw+zyxZjChckey2J5h4L6EtI7sNDJk12xtc9+mRO9SszQ=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=oracle.com;
Received: from DM6PR10MB3148.namprd10.prod.outlook.com (2603:10b6:5:1a4::21)
 by DM5PR1001MB2153.namprd10.prod.outlook.com (2603:10b6:4:2c::27) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3868.33; Wed, 24 Feb
 2021 14:05:05 +0000
Received: from DM6PR10MB3148.namprd10.prod.outlook.com
 ([fe80::f871:5965:2081:3934]) by DM6PR10MB3148.namprd10.prod.outlook.com
 ([fe80::f871:5965:2081:3934%5]) with mapi id 15.20.3868.033; Wed, 24 Feb 2021
 14:05:05 +0000
From: David Edmondson <david.edmondson@oracle.com>
To: linux-kernel@vger.kernel.org
Cc: Jim Mattson <jmattson@google.com>, Borislav Petkov <bp@alien8.de>,
        Joerg Roedel <joro@8bytes.org>,
        Vitaly Kuznetsov <vkuznets@redhat.com>, kvm@vger.kernel.org,
        Wanpeng Li <wanpengli@tencent.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Sean Christopherson <seanjc@google.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        "H. Peter Anvin" <hpa@zytor.com>, Ingo Molnar <mingo@redhat.com>,
        x86@kernel.org, David Edmondson <david.edmondson@oracle.com>
Subject: [PATCH v4 1/5] KVM: x86: dump_vmcs should not assume GUEST_IA32_EFER
 is valid
Date: Wed, 24 Feb 2021 14:04:52 +0000
Message-Id: <20210224140456.2558033-2-david.edmondson@oracle.com>
X-Mailer: git-send-email 2.30.0
In-Reply-To: <20210224140456.2558033-1-david.edmondson@oracle.com>
References: <20210224140456.2558033-1-david.edmondson@oracle.com>
X-Originating-IP: [2001:8b0:bb71:7140:64::1]
X-ClientProxiedBy: LO4P123CA0411.GBRP123.PROD.OUTLOOK.COM
 (2603:10a6:600:189::20) To DM6PR10MB3148.namprd10.prod.outlook.com
 (2603:10b6:5:1a4::21)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from disaster-area.hh.sledj.net (2001:8b0:bb71:7140:64::1) by
 LO4P123CA0411.GBRP123.PROD.OUTLOOK.COM (2603:10a6:600:189::20) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3868.30 via Frontend
 Transport; Wed, 24 Feb 2021 14:05:02 +0000
Received: from localhost (disaster-area.hh.sledj.net [local])   by
 disaster-area.hh.sledj.net (OpenSMTPD) with ESMTPA id 944eff70;
      Wed, 24 Feb 2021 14:04:56 +0000 (UTC)
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: e68395ac-0e4a-410b-7075-08d8d8cd2f58
X-MS-TrafficTypeDiagnostic: DM5PR1001MB2153:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM5PR1001MB2153D596061B0EF9891252E5889F9@DM5PR1001MB2153.namprd10.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:6790;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 wB4+ej7U034mHS0SHaNRvn8kwigRFLkUoSt+BewLaSlSYbPDShcIu54K7SpBN756L3dy2tNUKKrFEeleOD60Ral5LFQ17WBaAyY4HsEeVIv7fAj1jFelmOsLkyBHjyCvzOR+EMZWQnM1VVmhcVfQrrSujOev3FVvHfirpjvQ4wbHT2yFUdKbHLQJ0x34LfoGj7PYwB6Ow2531bWM9i1TY/QUmZgpQej3Jyce8uFUtdv12w0NtxObamdknRwuFxqyi1bQVoYP58U33xmhHMCLzbpZazzVjHsfvTDqIJO5LkEQ4g1B2eSzg+NbF1SsZHMg7hB0IMpGdhL7LeoLS5OKd42I5AE1gXoImF3jjnXi38J52lqt8c37GuXA94epnwKd3E1lTfVMQu2fXvCSH3RjRd2pm/VIseAkSSJ8SLH9PRbnjNfUorCieKaiyDmcifikU+13TLv1ciZNcql+jqCrFu7xWZ3E8Qa2ycyAORLkpr1B5wM30f9av7459Hg7mxt5leJwYIV79R/i1eN4hUan8g==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR10MB3148.namprd10.prod.outlook.com;PTR:;CAT:NONE;SFS:(136003)(39860400002)(346002)(396003)(366004)(376002)(83380400001)(316002)(66476007)(44832011)(8936002)(186003)(2906002)(86362001)(7416002)(8676002)(66556008)(52116002)(36756003)(5660300002)(6916009)(54906003)(1076003)(2616005)(4326008)(6666004)(478600001)(66946007)(107886003);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 2Ob9BIjMsmjxaRcKdwQ5+XOuud+YeB+17Wv8mZyJcN2KQqrOH5n+ndrW9mdRY24Fhyc52uO1+I8HT0StifxhfIwdcOYkhvsl2ClBYhRRfKqj9luKmK4vVfZhKpL5v6B1GmmPrrPdmwKg6SgGjXf52Nakk2SpptehFeQFCt6P1T5vrUtq6lw8pvXKSBjSRxKraxtFYswZDtMAoSj4bR5bqRhT2vYqRJswK/w4QNcGtVveepZRy5pFGN3SWOOa9RNeRfLhA08XYfyPQVorBLqs43bScdFHSkZkMcD8IXIDFc8lsb1ISoaSIejIw+XarawDMANqNOdhu8nINU93FhdXCkSPoOYA165ahHHKaoFwW1FkdX9gyZgkwwHefaIYv2AZqVXq/7HjTb71x2VoucU5+QnaCduvRYcuEERm6f+UN1qCHZbZVIX1ids0W4mkTszqDwbSfaIT7E7j29U6dNDrpR/wbluKu/rvsMWm0e0bPvzzEzHCo07iPiyeyM/i2JEUquT6EnT5M+ZEg/P0T/DwPIZxdc7b15BjLzg7Kla43FJv1TVskB7/ULmOH3OlTHJQr4YKC2S3EhzJJpkui/ZgMSEqfmsx+7Doq/emaUKnSUhTwXR9s2L7qcNOMh9oBwyzsyc8xtA87NpOAsxjpR0a5hBk8T9OVT3pBPz2r9DillSaQnnKX4PlJzN124hiXC/lziMe/27yX2+2aCgcPMDC+dFcmZxqJqepcioFi+W1YfSG3Ns3Jt6gbyFSwJXyftlW93labRZAgeVHf9KaWli8dnE3MdOvSEUPMEnDT3v9H0oAPBZ+hk8UieH1wrQ7OwP4FAYUaeNm4RxFAFvLb6kuLFJRBNS8ePmeHKuTxZXuAX/QiV1gfC/YQkpLAowM+SxwP3JIVHtJk/Oq6Ui8zjRmZQvg6h8qxdx5xXF3OoYfYCEfMVHLNgLmjpkAJpOJwsWs/m25TgjgyQdU3Ork0wmFFf6W3BHprBDzt0NGZiniiVMMjgKinOpqMFlceyBZnzpfcLTPwq3rx2Zr8+J+bF0ci4pCv2rKcPrMzQ6PKrwPgwQJZazz4oxKqXizQyvDer1akLX7ErA9DSkVSavB2+e2W1Qu/ov1v3AfOYF+TK4K4S37eoSBcjKIiJiw4eZyqCiclwD4VRNR1ecMWbpljGd+ZOBf7C0FulS5d8e/eKUTG1javXNvH9CSYdGNzE1pnVmKRiuLbvs5bknLMGArS+VBaysjwgjrb29lIlROxV0SioRd4CWQRiCCAAaAeH00yGH2fYYaPqSRFiVFwZSxOrLGszaunFsKR6tGWfk28eyr9WYenOOQYpjTlEvHPEhMhTkZsuCWSNJpPXeILR+dUhIWYA==
X-OriginatorOrg: oracle.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 e68395ac-0e4a-410b-7075-08d8d8cd2f58
X-MS-Exchange-CrossTenant-AuthSource: DM6PR10MB3148.namprd10.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 24 Feb 2021 14:05:04.9784
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 4e2c6054-71cb-48f1-bd6c-3a9705aca71b
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 ijYw2SmaYyLZPEWi++pqIU/zZoyLCGgK4Lt07nAK7IR41Ci/wbfLmGFdaupgBd3Xy0E8qLQBzCM8OkBxY0kOuLMNBOOiQI0rIzdrfTfIDKA=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM5PR1001MB2153
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9904
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 spamscore=0
 suspectscore=0
 malwarescore=0 mlxlogscore=966 adultscore=0 bulkscore=0 mlxscore=0
 phishscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102240108
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9904
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=0
 bulkscore=0
 clxscore=1015 mlxlogscore=999 lowpriorityscore=0 phishscore=0
 impostorscore=0 adultscore=0 mlxscore=0 priorityscore=1501 malwarescore=0
 spamscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102240109
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If the VM entry/exit controls for loading/saving MSR_EFER are either
not available (an older processor or explicitly disabled) or not
used (host and guest values are the same), reading GUEST_IA32_EFER
from the VMCS returns an inaccurate value.

Because of this, in dump_vmcs() don't use GUEST_IA32_EFER to decide
whether to print the PDPTRs - always do so if the fields exist.

Fixes: 4eb64dce8d0a ("KVM: x86: dump VMCS on invalid entry")
Signed-off-by: David Edmondson <david.edmondson@oracle.com>

if valid
---
 arch/x86/kvm/vmx/vmx.c | 9 +++------
 1 file changed, 3 insertions(+), 6 deletions(-)

```
#### [PATCH] KVM: x86: Remove the best->function == 0x7 assignment
##### From: Yejune Deng <yejune.deng@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yejune Deng <yejune.deng@gmail.com>
X-Patchwork-Id: 12101171
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C3AE5C433DB
	for <kvm@archiver.kernel.org>; Wed, 24 Feb 2021 02:30:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 85F1464DBD
	for <kvm@archiver.kernel.org>; Wed, 24 Feb 2021 02:30:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232536AbhBXCaY (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 23 Feb 2021 21:30:24 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:42760 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232069AbhBXCaW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 23 Feb 2021 21:30:22 -0500
Received: from mail-pj1-x102b.google.com (mail-pj1-x102b.google.com
 [IPv6:2607:f8b0:4864:20::102b])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 75011C06174A;
        Tue, 23 Feb 2021 18:29:42 -0800 (PST)
Received: by mail-pj1-x102b.google.com with SMTP id cx11so290248pjb.4;
        Tue, 23 Feb 2021 18:29:42 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=IajG/oRx8DIcPZiXA2gvIdGxbCLN+T0yMKe3hbjtvHY=;
        b=WZ9ZVIVbhgU9SCIeRL7TJpUayGh+VpyEEWCoPIqYi0RIuD/hvg6Vh3oA3wlAGtRTFn
         p7/rPV2tKcX6kvjrQi3QFWmrYwt/HeU5StRtsKLXQ8dwCl2s2l1o4GpzVApHI1jVb+rb
         h0gg2vgaxjQJQBeC4uQN+cIC6gKQwRYzakqB8LXSE8IJfRfXSmIRyowot+x8xISfTn8g
         nWQa5DiYf21D7SAvvOfRmICEyla1gpH8PA9AGCIubCB/dDswbFMxSbBYlL56pWpti1Zx
         fmjmNpEIuBMroKpYPZM7NHeT9S6RHtXcMy5yifbB0yxMQ+85/X0v3eGA2niYyJCrv4oQ
         ShgQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=IajG/oRx8DIcPZiXA2gvIdGxbCLN+T0yMKe3hbjtvHY=;
        b=eYOPcN1OncyLFcZkbC1Q5mQkB/KdomphuEhfFJaISs6kGVBFzcDUnwYvc27Z0rSyjl
         U03egM/pDxhVJksSclIyjw6fnunpuD56uk9hystp3VO/6Hg5uugsOlq/c3ekRlEGfeOy
         0BdTWLHJOlIwUkMry7ogzah8o03Oronz4CCCmVFEkZWJgPgYGwb0eypbntV/Y6xiQWlf
         kJrUCwnJ0JbygltwMdsbjrdDb32HkbHaE4rAIONdiJgyZZuLWufsR+202fsTk/9EInhp
         +EEe4+1dnL2u2MSJDCEYpWTTtKu6vhi8nSX++z5rxKLYAZ2nceaSgQbEVl/1Yd0hjaBS
         K/Sg==
X-Gm-Message-State: AOAM531slw2RCE63V7VkI7/uVBQtrGlrM+Xq1+aSl4Z8xHxMny0aP+Wd
        Vv88JlexCobANVyb/Dwu9Ujsp921fiTmmg==
X-Google-Smtp-Source: 
 ABdhPJxaf1+fVqWgvbh/vW3PyzmVkyvu9VCjv5RZq5CIjP+dEEFF/Bk8dwOYmRbg1wYdJgWdy0Qzbg==
X-Received: by 2002:a17:902:7592:b029:e2:e80f:6893 with SMTP id
 j18-20020a1709027592b02900e2e80f6893mr30661718pll.61.1614133782016;
        Tue, 23 Feb 2021 18:29:42 -0800 (PST)
Received: from localhost.localdomain ([122.10.161.207])
        by smtp.gmail.com with ESMTPSA id
 u128sm511452pfc.192.2021.02.23.18.29.38
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 23 Feb 2021 18:29:41 -0800 (PST)
From: Yejune Deng <yejune.deng@gmail.com>
To: pbonzini@redhat.com, seanjc@google.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        tglx@linutronix.de, mingo@redhat.com, bp@alien8.de, x86@kernel.org,
        hpa@zytor.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        yejune.deng@gmail.com
Subject: [PATCH] KVM: x86: Remove the best->function == 0x7 assignment
Date: Wed, 24 Feb 2021 10:29:31 +0800
Message-Id: <20210224022931.14094-1-yejune.deng@gmail.com>
X-Mailer: git-send-email 2.29.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In kvm_update_cpuid_runtime(), there is no need the best->function
== 0x7 assignment, because there is e->function == function in
cpuid_entry2_find().

Signed-off-by: Yejune Deng <yejune.deng@gmail.com>
Reviewed-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/kvm/cpuid.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [RFC] KVM: x86: Support KVM VMs sharing SEV contextFrom: Nathan Tempelman <natet@google.com>
##### From: Nathan Tempelman <natet@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nathan Tempelman <natet@google.com>
X-Patchwork-Id: 12101543
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A6D99C433DB
	for <kvm@archiver.kernel.org>; Wed, 24 Feb 2021 09:01:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 28D5464E24
	for <kvm@archiver.kernel.org>; Wed, 24 Feb 2021 09:01:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232563AbhBXJBD (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 24 Feb 2021 04:01:03 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:41398 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231607AbhBXJAy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 24 Feb 2021 04:00:54 -0500
Received: from mail-pf1-x449.google.com (mail-pf1-x449.google.com
 [IPv6:2607:f8b0:4864:20::449])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 1239BC06174A
        for <kvm@vger.kernel.org>; Wed, 24 Feb 2021 01:00:14 -0800 (PST)
Received: by mail-pf1-x449.google.com with SMTP id e199so1420298pfh.11
        for <kvm@vger.kernel.org>; Wed, 24 Feb 2021 01:00:13 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=xND5NPzVXfLcbqvng9kSRm35uak6gASQPEje4KIW2sA=;
        b=Q1DdZaQStS40ic6KaBUaznLddsLyINwWVJb+JB6SFucjVubHP8iiXYYFmRABzR89XG
         r2VV2WfBXrUNGR9iwZfgpO8pht2wzI7KJKJieqqqaYfCn2YS2DpSm3n9eXpN+wPG0DWi
         CNg6lLKgvbEDD11OXbl+I25vLw87mKWr8YRnQIAD+rt0q/pukrM6xqo1ijMMaBU63jA1
         mBnIgc8+3e5j6YyCwOU+/Er9/ldS10YtasQDKxs1yO82XCh3rI12Wp3j7dFdOUul4WRp
         pzhZFeC0XVbDQ9MCIvSfmE8mzEoiivSyGI8ZvJ8j2jyLeTZ8L/KgbvDggjHT2i7yn6PD
         xPQg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=xND5NPzVXfLcbqvng9kSRm35uak6gASQPEje4KIW2sA=;
        b=XZLumKy74Bq2++McdcPHlK8VAzhbbv0hSQzcdDy4KiLpHikNL6+KasBGVKQPMsq8qz
         9fv9cnmxlZHbNCSvw+fUIIVrJwpglAeI/vPPRS2M3nCl+LG+ffIHhBJoUNx1TlGSVpdw
         q3TOZp/w7vv9bTg4hmVWu9HQ4hBEV9N3ElXD00IUcPA7wMfLW2NdFtayfoKEwaWvp1sL
         cCvd9bKneMLRXescA40HhiuvQekJHjTbdNeT8ZUG5YdQfE7JFkLPpfJhjmxH/yK3CUsh
         lPsIGLqJ3qIOoqcpsMU3P0edg/c5ss1by/iWB+vFnPsUqM5hGpWEaxwXCSGZXlC8/+cf
         0eJw==
X-Gm-Message-State: AOAM530MyXHDfljC2E0s5Rbyn70kB20dDuI7swnWA/wwhvuELvXuBmKU
        Z7+dys7v/7MMChoViaGbWDyzn8ujvg==
X-Google-Smtp-Source: 
 ABdhPJyCgOMbxMWcaSPF6FC9POMDZNNUmc5ybqqQS3quJMs+8n4Jm271E9ajaFsSyEAXSkkk7Y/VuAOKRQ==
Sender: "natet via sendgmr" <natet@natesp.c.googlers.com>
X-Received: from natesp.c.googlers.com ([fda3:e722:ac3:10:24:72f4:c0a8:5758])
 (user=natet job=sendgmr) by 2002:a17:902:ed82:b029:e2:d106:e76d with SMTP id
 e2-20020a170902ed82b02900e2d106e76dmr30689065plj.46.1614157213381; Wed, 24
 Feb 2021 01:00:13 -0800 (PST)
Date: Wed, 24 Feb 2021 08:59:15 +0000
Message-Id: <20210224085915.28751-1-natet@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.0.617.g56c4b15f3c-goog
Subject: [RFC] KVM: x86: Support KVM VMs sharing SEV context
From: Nathan Tempelman <natet@google.com>
To: pbonzini@redhat.com
Cc: natet@google.com, thomas.lendacky@amd.com, x86@kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        srutherford@google.com, seanjc@google.com, rientjes@google.com,
        brijesh.singh@amd.com, Ashish.Kalra@amd.com
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add a capability for userspace to mirror SEV encryption context from
one vm to another. On our side, this is intended to support a
Migration Helper vCPU, but it can also be used generically to support
other in-guest workloads scheduled by the host. The intention is for
the primary guest and the mirror to have nearly identical memslots.

The primary benefits of this are that:
1) The VMs do not share KVM contexts (think APIC/MSRs/etc), so they
can't accidentally clobber each other.
2) The VMs can have different memory-views, which is necessary for post-copy
migration (the migration vCPUs on the target need to read and write to
pages, when the primary guest would VMEXIT).

This does not change the threat model for AMD SEV. Any memory involved
is still owned by the primary guest and its initial state is still
attested to through the normal SEV_LAUNCH_* flows. If userspace wanted
to circumvent SEV, they could achieve the same effect by simply attaching
a vCPU to the primary VM.
This patch deliberately leaves userspace in charge of the memslots for the
mirror, as it already has the power to mess with them in the primary guest.

This patch does not support SEV-ES (much less SNP), as it does not
handle handing off attested VMSAs to the mirror.

For additional context, we need a Migration Helper because SEV PSP migration
is far too slow for our live migration on its own. Using an in-guest
migrator lets us speed this up significantly.

Signed-off-by: Nathan Tempelman <natet@google.com>
---
 Documentation/virt/kvm/api.rst  | 17 +++++++
 arch/x86/include/asm/kvm_host.h |  1 +
 arch/x86/kvm/svm/sev.c          | 82 +++++++++++++++++++++++++++++++++
 arch/x86/kvm/svm/svm.c          |  2 +
 arch/x86/kvm/svm/svm.h          |  2 +
 arch/x86/kvm/x86.c              |  7 ++-
 include/linux/kvm_host.h        |  1 +
 include/uapi/linux/kvm.h        |  1 +
 virt/kvm/kvm_main.c             |  8 ++++
 9 files changed, 120 insertions(+), 1 deletion(-)

```
#### [PATCH v7 1/2] drivers/misc: sysgenid: add system generation id driver
##### From: Adrian Catangiu <acatan@amazon.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Adrian Catangiu <acatan@amazon.com>
X-Patchwork-Id: 12101533
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C2E6CC43332
	for <kvm@archiver.kernel.org>; Wed, 24 Feb 2021 08:50:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8D1EC600CC
	for <kvm@archiver.kernel.org>; Wed, 24 Feb 2021 08:50:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234590AbhBXIu1 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 24 Feb 2021 03:50:27 -0500
Received: from smtp-fw-2101.amazon.com ([72.21.196.25]:20716 "EHLO
        smtp-fw-2101.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S234196AbhBXItT (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 24 Feb 2021 03:49:19 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1614156553; x=1645692553;
  h=from:to:cc:subject:date:message-id:in-reply-to:
   references:mime-version;
  bh=LimMPlxvzJqW0k0WBEnn6q/6+b58DuWNihC6svuyPGg=;
  b=OSqJ4aSSwgoQit/zYb/JrKcj/zAkvcCtW9MC7U1b8fon2X1N/rBDBinb
   ib7AWSs2XXBNfsTsMyBAQKxHvDz9tcSAnBvkR3Am9KTkAfajLdLVmYfSq
   COz3OargbCeToC3yD2aug2axeaxo/nJLsOTsBQLlBOqx0ZiXa7hcK6ddY
   4=;
X-IronPort-AV: E=Sophos;i="5.81,202,1610409600";
   d="scan'208";a="87370351"
Received: from iad12-co-svc-p1-lb1-vlan3.amazon.com (HELO
 email-inbound-relay-1a-af6a10df.us-east-1.amazon.com) ([10.43.8.6])
  by smtp-border-fw-out-2101.iad2.amazon.com with ESMTP;
 24 Feb 2021 08:48:24 +0000
Received: from EX13D08EUB004.ant.amazon.com
 (iad12-ws-svc-p26-lb9-vlan3.iad.amazon.com [10.40.163.38])
        by email-inbound-relay-1a-af6a10df.us-east-1.amazon.com (Postfix) with
 ESMTPS id 021D6A2303;
        Wed, 24 Feb 2021 08:48:12 +0000 (UTC)
Received: from uf6ed9c851f4556.ant.amazon.com (10.43.160.157) by
 EX13D08EUB004.ant.amazon.com (10.43.166.158) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Wed, 24 Feb 2021 08:47:56 +0000
From: Adrian Catangiu <acatan@amazon.com>
To: <linux-doc@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
        <qemu-devel@nongnu.org>, <kvm@vger.kernel.org>,
        <linux-s390@vger.kernel.org>
CC: <gregkh@linuxfoundation.org>, <graf@amazon.com>,
        <rdunlap@infradead.org>, <arnd@arndb.de>, <ebiederm@xmission.com>,
        <rppt@kernel.org>, <0x7f454c46@gmail.com>,
        <borntraeger@de.ibm.com>, <Jason@zx2c4.com>, <jannh@google.com>,
        <w@1wt.eu>, <colmmacc@amazon.com>, <luto@kernel.org>,
        <tytso@mit.edu>, <ebiggers@kernel.org>, <dwmw@amazon.co.uk>,
        <bonzini@gnu.org>, <sblbir@amazon.com>, <raduweis@amazon.com>,
        <corbet@lwn.net>, <mst@redhat.com>, <mhocko@kernel.org>,
        <rafael@kernel.org>, <pavel@ucw.cz>, <mpe@ellerman.id.au>,
        <areber@redhat.com>, <ovzxemul@gmail.com>, <avagin@gmail.com>,
        <ptikhomirov@virtuozzo.com>, <gil@azul.com>, <asmehra@redhat.com>,
        <dgunigun@redhat.com>, <vijaysun@ca.ibm.com>, <oridgar@gmail.com>,
        <ghammer@redhat.com>, Adrian Catangiu <acatan@amazon.com>
Subject: [PATCH v7 1/2] drivers/misc: sysgenid: add system generation id
 driver
Date: Wed, 24 Feb 2021 10:47:31 +0200
Message-ID: <1614156452-17311-2-git-send-email-acatan@amazon.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1614156452-17311-1-git-send-email-acatan@amazon.com>
References: <1614156452-17311-1-git-send-email-acatan@amazon.com>
MIME-Version: 1.0
X-Originating-IP: [10.43.160.157]
X-ClientProxiedBy: EX13D38UWC002.ant.amazon.com (10.43.162.46) To
 EX13D08EUB004.ant.amazon.com (10.43.166.158)
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

- Background and problem

The System Generation ID feature is required in virtualized or
containerized environments by applications that work with local copies
or caches of world-unique data such as random values, uuids,
monotonically increasing counters, etc.
Such applications can be negatively affected by VM or container
snapshotting when the VM or container is either cloned or returned to
an earlier point in time.

Furthermore, simply finding out about a system generation change is
only the starting point of a process to renew internal states of
possibly multiple applications across the system. This process requires
a standard interface that applications can rely on and through which
orchestration can be easily done.

- Solution

The System Generation ID is meant to help in these scenarios by
providing a monotonically increasing u32 counter that changes each time
the VM or container is restored from a snapshot.

The `sysgenid` driver exposes a monotonic incremental System Generation
u32 counter via a char-dev filesystem interface accessible
through `/dev/sysgenid`. It provides synchronous and asynchronous SysGen
counter update notifications, as well as counter retrieval and
confirmation mechanisms.
The counter starts from zero when the driver is initialized and
monotonically increments every time the system generation changes.

Userspace applications or libraries can (a)synchronously consume the
system generation counter through the provided filesystem interface, to
make any necessary internal adjustments following a system generation
update.

The provided filesystem interface operations can be used to build a
system level safe workflow that guest software can follow to protect
itself from negative system snapshot effects.

The `sysgenid` driver exports the `void sysgenid_bump_generation()`
symbol which can be used by backend drivers to drive system generation
changes based on hardware events.
System generation changes can also be driven by userspace software
through a dedicated driver ioctl.

**Please note**, SysGenID alone does not guarantee complete snapshot
safety to applications using it. A certain workflow needs to be
followed at the system level, in order to make the system
snapshot-resilient. Please see the "Snapshot Safety Prerequisites"
section in the included documentation.

Signed-off-by: Adrian Catangiu <acatan@amazon.com>
---
 Documentation/misc-devices/sysgenid.rst            | 229 +++++++++++++++
 Documentation/userspace-api/ioctl/ioctl-number.rst |   1 +
 MAINTAINERS                                        |   8 +
 drivers/misc/Kconfig                               |  15 +
 drivers/misc/Makefile                              |   1 +
 drivers/misc/sysgenid.c                            | 322 +++++++++++++++++++++
 include/uapi/linux/sysgenid.h                      |  18 ++
 7 files changed, 594 insertions(+)
 create mode 100644 Documentation/misc-devices/sysgenid.rst
 create mode 100644 drivers/misc/sysgenid.c
 create mode 100644 include/uapi/linux/sysgenid.h

diff --git a/Documentation/misc-devices/sysgenid.rst b/Documentation/misc-devices/sysgenid.rst
new file mode 100644
index 0000000..0b8199b
--- /dev/null
+++ b/Documentation/misc-devices/sysgenid.rst
@@ -0,0 +1,229 @@
+.. SPDX-License-Identifier: GPL-2.0
+
+========
+SYSGENID
+========
+
+The System Generation ID feature is required in virtualized or
+containerized environments by applications that work with local copies
+or caches of world-unique data such as random values, UUIDs,
+monotonically increasing counters, etc.
+Such applications can be negatively affected by VM or container
+snapshotting when the VM or container is either cloned or returned to
+an earlier point in time.
+
+The System Generation ID is meant to help in these scenarios by
+providing a monotonically increasing counter that changes each time the
+VM or container is restored from a snapshot. The driver for it lives at
+``drivers/misc/sysgenid.c``.
+
+The ``sysgenid`` driver exposes a monotonic incremental System
+Generation u32 counter via a char-dev filesystem interface accessible
+through ``/dev/sysgenid`` that provides sync and async SysGen counter
+update notifications. It also provides SysGen counter retrieval and
+confirmation mechanisms.
+
+The counter starts from zero when the driver is initialized and
+monotonically increments every time the system generation changes.
+
+The ``sysgenid`` driver exports the ``void sysgenid_bump_generation()``
+symbol which can be used by backend drivers to drive system generation
+changes based on hardware events.
+System generation changes can also be driven by userspace software
+through a dedicated driver ioctl.
+
+Userspace applications or libraries can (a)synchronously consume the
+system generation counter through the provided filesystem interface, to
+make any necessary internal adjustments following a system generation
+update.
+
+**Please note**, SysGenID alone does not guarantee complete snapshot
+safety to applications using it. A certain workflow needs to be
+followed at the system level, in order to make the system
+snapshot-resilient. Please see the "Snapshot Safety Prerequisites"
+section below.
+
+Driver filesystem interface
+===========================
+
+``open()``:
+  When the device is opened, a copy of the current SysGenID (counter)
+  is associated with the open file descriptor. Every open file
+  descriptor will have readable data available (EPOLLIN) while its
+  current copy of the SysGenID is outdated. Reading from the fd will
+  provide the latest SysGenID, while writing to the fd will update the
+  fd-local copy of the SysGenID and is used as a confirmation
+  mechanism.
+
+``read()``:
+  Read is meant to provide the *new* system generation counter when a
+  generation change takes place. The read operation blocks until the
+  associated counter is no longer up to date, at which point the new
+  counter is provided/returned.  Nonblocking ``read()`` returns
+  ``EAGAIN`` to signal that there is no *new* counter value available.
+  The generation counter is considered *new* for each open file
+  descriptor that hasn't confirmed the new value following a generation
+  change. Therefore, once a generation change takes place, all
+  ``read()`` calls will immediately return the new generation counter
+  and will continue to do so until the new value is confirmed back to
+  the driver through ``write()``.
+  Partial reads are not allowed - read buffer needs to be at least
+  32 bits in size.
+
+``write()``:
+  Write is used to confirm the up-to-date SysGenID counter back to the
+  driver.
+  Following a VM generation change, all existing watchers are marked
+  as *outdated*. Each file descriptor will maintain the *outdated*
+  status until a ``write()`` containing the new up-to-date generation
+  counter is used as an update confirmation mechanism.
+  Partial writes are not allowed - write buffer should be exactly
+  32 bits in size.
+
+``poll()``:
+  Poll is implemented to allow polling for generation counter updates.
+  Such updates result in ``EPOLLIN`` polling status until the new
+  up-to-date counter is confirmed back to the driver through a
+  ``write()``.
+
+``ioctl()``:
+  The driver also adds support for waiting on open file descriptors
+  that haven't acknowledged a generation counter update, as well as a
+  mechanism for userspace to *trigger* a generation update:
+
+  - SYSGENID_SET_WATCHER_TRACKING: takes a bool argument to set tracking
+    status for current file descriptor. When watcher tracking is
+    enabled, the driver tracks this file descriptor as an independent
+    *watcher*. The driver keeps accounting of how many watchers have
+    confirmed the latest Sys-Gen-Id counter and how many of them are
+    *outdated*; an outdated watcher is a *tracked* open file descriptor
+    that has lived through a Sys-Gen-Id change but has not yet confirmed
+    the new generation counter.
+    Software that wants to be waited on by the system while it adjusts
+    to generation changes, should turn tracking on. The sysgenid driver
+    then keeps track of it and can block system-level adjustment process
+    until the software has finished adjusting and confirmed it through a
+    ``write()``.
+    Tracking is disabled by default and file descriptors need to
+    explicitly opt-in using this IOCTL.
+  - SYSGENID_WAIT_WATCHERS: blocks until there are no more *outdated*
+    tracked watchers or, if a ``timeout`` argument is provided, until
+    the timeout expires.
+    If the current caller is *outdated* or a generation change happens
+    while waiting (thus making current caller *outdated*), the ioctl
+    returns ``-EINTR`` to signal the user to handle event and retry.
+  - SYSGENID_TRIGGER_GEN_UPDATE: triggers a generation counter increment.
+    It takes a ``minimum-generation`` argument which represents the
+    minimum value the generation counter will be set to. For example if
+    current generation is ``5`` and ``SYSGENID_TRIGGER_GEN_UPDATE(8)``
+    is called, the generation counter will increment to ``8``.
+    This IOCTL can only be used by processes with CAP_CHECKPOINT_RESTORE
+    or CAP_SYS_ADMIN capabilities.
+
+``mmap()``:
+  The driver supports ``PROT_READ, MAP_SHARED`` mmaps of a single page
+  in size. The first 4 bytes of the mapped page will contain an
+  up-to-date u32 copy of the system generation counter.
+  The mapped memory can be used as a low-latency generation counter
+  probe mechanism in critical sections.
+  The mmap() interface is targeted at libraries or code that needs to
+  check for generation changes in-line, where an event loop is not
+  available or read()/write() syscalls are too expensive.
+  In such cases, logic can be added in-line with the sensitive code to
+  check and trigger on-demand/just-in-time readjustments when changes
+  are detected on the memory mapped generation counter.
+  Users of this interface that plan to lazily adjust should not enable
+  watcher tracking, since waiting on them doesn't make sense.
+
+``close()``:
+  Removes the file descriptor as a system generation counter *watcher*.
+
+Snapshot Safety Prerequisites
+=============================
+
+If VM, container or other system-level snapshots happen asynchronously,
+at arbitrary times during an active workload there is no practical way
+to ensure that in-flight local copies or caches of world-unique data
+such as random values, secrets, UUIDs, etc are properly scrubbed and
+regenerated.
+The challenge stems from the fact that the categorization of data as
+snapshot-sensitive is only known to the software working with it, and
+this software has no logical control over the moment in time when an
+external system snapshot occurs.
+
+Let's take an OpenSSL session token for example. Even if the library
+code is made 100% snapshot-safe, meaning the library guarantees that
+the session token is unique (any snapshot that happened during the
+library call did not duplicate or leak the token), the token is still
+vulnerable to snapshot events while it transits the various layers of
+the library caller, then the various layers of the OS before leaving
+the system.
+
+To catch a secret while it's in-flight, we'd have to validate system
+generation at every layer, every step of the way. Even if that would
+be deemed the right solution, it would be a long road and a whole
+universe to patch before we get there.
+
+Bottom line is we don't have a way to track all of these in-flight
+secrets and dynamically scrub them from existence with snapshot
+events happening arbitrarily.
+
+Simplifyng assumption - safety prerequisite
+-------------------------------------------
+
+**Control the snapshot flow**, disallow snapshots coming at arbitrary
+moments in the workload lifetime.
+
+Use a system-level overseer entity that quiesces the system before
+snapshot, and post-snapshot-resume oversees that software components
+have readjusted to new environment, to the new generation. Only after,
+will the overseer un-quiesce the system and allow active workloads.
+
+Software components can choose whether they want to be tracked and
+waited on by the overseer by using the ``SYSGENID_SET_WATCHER_TRACKING``
+IOCTL.
+
+The sysgenid framework standardizes the API for system software to
+find out about needing to readjust and at the same time provides a
+mechanism for the overseer entity to wait for everyone to be done, the
+system to have readjusted, so it can un-quiesce.
+
+Example snapshot-safe workflow
+------------------------------
+
+1) Before taking a snapshot, quiesce the VM/container/system. Exactly
+   how this is achieved is very workload-specific, but the general
+   description is to get all software to an expected state where their
+   event loops dry up and they are effectively quiesced.
+2) Take snapshot.
+3) Resume the VM/container/system from said snapshot.
+4) SysGenID counter will either automatically increment if there is
+   a vmgenid backend (hw-driven), or overseer will trigger generation
+   bump using ``SYSGENID_TRIGGER_GEN_UPDATE`` IOCLT (sw-driven).
+5) Software components which have ``/dev/sysgenid`` in their event
+   loops (either using ``poll()`` or ``read()``) are notified of the
+   generation change.
+   They do their specific internal adjustments. Some may have requested
+   to be tracked and waited on by the overseer, others might choose to
+   do their adjustments out of band and not block the overseer.
+   Tracked ones *must* signal when they are done/ready with a ``write()``
+   while the rest *should* also do so for cleanliness, but it's not
+   mandatory.
+6) Overseer will block and wait for all tracked watchers by using the
+   ``SYSGENID_WAIT_WATCHERS`` IOCTL. Once all tracked watchers are done
+   in step 5, this overseer will return from this blocking ioctl knowing
+   that the system has readjusted and is ready for active workload.
+7) Overseer un-quiesces system.
+8) There is a class of software, usually libraries, most notably PRNGs
+   or SSLs, that don't fit the event-loop model and also have strict
+   latency requirements. These can take advantage of the ``mmap()``
+   interface and lazily adjust on-demand whenever they are called after
+   un-quiesce.
+   For a well-designed service stack, these libraries should not be
+   called while system is quiesced. When workload is resumed by the
+   overseer, on the first call into these libs, they will safely JIT
+   readjust.
+   Users of this lazy on-demand readjustment model should not enable
+   watcher tracking since doing so would introduce a logical deadlock:
+   lazy adjustments happen only after un-quiesce, but un-quiesce is
+   blocked until all tracked watchers are up-to-date.
```
#### [PATCH v4] KVM: kvmclock: Fix vCPUs > 64 can't be online/hotpluged
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 12101169
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9BF97C433DB
	for <kvm@archiver.kernel.org>; Wed, 24 Feb 2021 01:39:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 62BC564E7A
	for <kvm@archiver.kernel.org>; Wed, 24 Feb 2021 01:39:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231569AbhBXBjB (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 23 Feb 2021 20:39:01 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:60042 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229791AbhBXBiz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 23 Feb 2021 20:38:55 -0500
Received: from mail-pf1-x429.google.com (mail-pf1-x429.google.com
 [IPv6:2607:f8b0:4864:20::429])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id B917EC061574;
        Tue, 23 Feb 2021 17:38:14 -0800 (PST)
Received: by mail-pf1-x429.google.com with SMTP id j12so215055pfj.12;
        Tue, 23 Feb 2021 17:38:14 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=PCXVBw+FVq9Qv7Zgo9oRjK2xe7y4k5Oj/v44tVkJbo0=;
        b=BzANR0kJ0Fql1BVqLO7DnIkZ3agBiRBMZ6/U31p70gakfCYgStJ2M0NxYbDiAv3wkO
         LTDQUJ4IMBxPgO6kNi637XPnIHwEaXrzNIDl353nkG5ilyHai6E1AB8V4DUATcjiqaN7
         nNVuSbD1a4znNNpqlVh37CG9HBQ/mw5ggtCeQC2ntjUjQYNrVXsikK9GPNRdqGt+bgF+
         nx8wPq/dFdkPwIokb1paqGOvAWznX7lkiDwMFUPQi4O0nXHr7mDDaa/JD5RDRExDt3xk
         K3jxbe9Lq3FxryDETbMhX/evp7ZGqAvtFeCOzNtUy5WI21u5Q7c8RfQSQRcQhRM8DScQ
         nilQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=PCXVBw+FVq9Qv7Zgo9oRjK2xe7y4k5Oj/v44tVkJbo0=;
        b=FJCh2tXVGbUwcXCxlBn39H1/1ilfvXxAcGEBDogfIo1gGl0Pjaop8tmvXrX3QCNp2I
         kuSSnnRjigNLwPyWlb3hWcKKBjHkLGA+tFS36Uk6lyGy9DTSsHJFLEbBf9TqyS4Nb0Fj
         O7kC/PWRdA3gGETRqftlg7EcM0hxfiOnqkp/qae1vcyQTQpIlfOyujqm4rm0fXxwxD2R
         8IM3clPZSQkmhwWYhxW7DVC6VWg1BIIy8IlvX14Um+RQq/cAsBXfKrcY+YdS6zrj1+1f
         WXkqQ+6V1Msi6rGAGHVXmVwpcEo23+IGfJCtGrfyWPuv+bylIFDJaX8/Mk0i+n4oNKGe
         pEGg==
X-Gm-Message-State: AOAM532OWHcB6f5p5oDPcHEdaCQqBCbSRcbhhnuOKCT9/y0uc+WfVg77
        V19/qma9T0fQXxc9eMUr1FCVeAVau+Y=
X-Google-Smtp-Source: 
 ABdhPJzJshRJmbbt1UgbHujf4RlK2kPBVuv+u8LI9fmqOatvvdvhrMXceRut6hmhsPt2Imd1dKNXiQ==
X-Received: by 2002:a63:da03:: with SMTP id c3mr25765435pgh.176.1614130693933;
        Tue, 23 Feb 2021 17:38:13 -0800 (PST)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 g141sm422496pfb.67.2021.02.23.17.38.11
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 23 Feb 2021 17:38:13 -0800 (PST)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Brijesh Singh <brijesh.singh@amd.com>
Subject: [PATCH v4] KVM: kvmclock: Fix vCPUs > 64 can't be online/hotpluged
Date: Wed, 24 Feb 2021 09:37:29 +0800
Message-Id: <1614130683-24137-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

# lscpu
Architecture:          x86_64
CPU op-mode(s):        32-bit, 64-bit
Byte Order:            Little Endian
CPU(s):                88
On-line CPU(s) list:   0-63
Off-line CPU(s) list:  64-87

# cat /proc/cmdline
BOOT_IMAGE=/vmlinuz-5.10.0-rc3-tlinux2-0050+ root=/dev/mapper/cl-root ro 
rd.lvm.lv=cl/root rhgb quiet console=ttyS0 LANG=en_US .UTF-8 no-kvmclock-vsyscall

# echo 1 > /sys/devices/system/cpu/cpu76/online
-bash: echo: write error: Cannot allocate memory

The per-cpu vsyscall pvclock data pointer assigns either an element of the 
static array hv_clock_boot (#vCPU <= 64) or dynamically allocated memory 
hvclock_mem (vCPU > 64), the dynamically memory will not be allocated if 
kvmclock vsyscall is disabled, this can result in cpu hotpluged fails in 
kvmclock_setup_percpu() which returns -ENOMEM. It's broken for no-vsyscall
and sometimes you end up with vsyscall disabled if the host does something 
strange. This patch fixes it by allocating this dynamically memory 
unconditionally even if vsyscall is disabled.

Fixes: 6a1cac56f4 ("x86/kvm: Use __bss_decrypted attribute in shared variables")
Reported-by: Zelin Deng <zelin.deng@linux.alibaba.com>
Cc: Brijesh Singh <brijesh.singh@amd.com>
Cc: stable@vger.kernel.org#v4.19-rc5+
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
v3 -> v4:
 * fix kernel test robot report WARNING
v2 -> v3:
 * allocate dynamically memory unconditionally
v1 -> v2:
 * add code comments

 arch/x86/kernel/kvmclock.c | 19 +++++++++----------
 1 file changed, 9 insertions(+), 10 deletions(-)

```
#### [PATCH] vhost_vdpa: fix the missing irq_bypass_unregister_producer() invocation
##### From: Gautam Dawar <gdawar.xilinx@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Gautam Dawar <gdawar.xilinx@gmail.com>
X-Patchwork-Id: 12101725
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D553FC433E6
	for <kvm@archiver.kernel.org>; Wed, 24 Feb 2021 11:50:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7DC4064DF3
	for <kvm@archiver.kernel.org>; Wed, 24 Feb 2021 11:50:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235065AbhBXLui (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 24 Feb 2021 06:50:38 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:49390 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S234493AbhBXLt4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 24 Feb 2021 06:49:56 -0500
Received: from mail-pg1-x532.google.com (mail-pg1-x532.google.com
 [IPv6:2607:f8b0:4864:20::532])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 28717C061574;
        Wed, 24 Feb 2021 03:49:16 -0800 (PST)
Received: by mail-pg1-x532.google.com with SMTP id o38so1269733pgm.9;
        Wed, 24 Feb 2021 03:49:16 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=iKXu5MTD/qNOkcWSg8bnOE00gDFp+RLdj201NypZGkc=;
        b=KKBBnpxYRiqICn8VUoFHfqlpocIoktHL4QfBR1OT8Xvc1+/veBc+D5nj8QMdgbjEwK
         1yes/Xz/5+dBGfZfK5rBMgrvkm8wyTUv9ozrjZqeorOJwYfVaXIgvVOeaTxScEgm6uxe
         ShSM1T4kGf/HKJ7o92OvMPKvMd2MtMwNXJfpv4zWmtN4vZFk68JK9AeETv6DaSkPTaX2
         Q0eNTMfrQyKvVO3cB9nEzDjn+uugTxpR1NA/SAkxX9dttovsdlENoepSTauut08ZtS6D
         RIhc0TTMYYczzbwHhAkg659qMxVfsalOutdE5pYFZ7KFyMTQEQL71StaqkENpqS+OQ3X
         YjkQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=iKXu5MTD/qNOkcWSg8bnOE00gDFp+RLdj201NypZGkc=;
        b=jBR5EKN+RAZu9+d/+Mw8Ko/X5j/u7FZMe3lAG+5267MG1+J8SstH2PfBCdx+DmsXEi
         MQX+BjkaVsYiQtZEZ+AfxokNds97PIRUl18lYrc9oO9DqYFbSCdmbp5uHsyP1Ozy68q6
         XKN/RS10fwtPwjZclaqtXpLGmx5IE/iVf+qPbth+lJpdIMwzt/ypqkshgvwdsjpVqbLU
         gdXQDjVXUu/3ERS1T8fz/1nyBbx9h/YPBDPhIehqWEJs6hyfWAHrImqDGkfVlf0EMaHN
         E1134jmcY16kbhgQEJgXG/6bKml5lBehFHbOyxkY5QIYynEOi3bpti5ZbzJjRBaVvY3D
         72hQ==
X-Gm-Message-State: AOAM531QAYrBKid6nlhvoyluTFIFc7oziyMzvxg1SeLJYpfHywzeKUqs
        mqUaaVtbVH8CEv6FDoGXr9Xg0JBc1MplMLzv
X-Google-Smtp-Source: 
 ABdhPJy6zT+ozN8jYuxk5CjeXkIK3JoA1vELHsGjU/enp38Jl4Qv64XF+ot1sMiM9QL4epMFQG0Dlw==
X-Received: by 2002:a05:6a00:16c7:b029:1bc:6eb9:ee47 with SMTP id
 l7-20020a056a0016c7b02901bc6eb9ee47mr32285893pfc.0.1614167355611;
        Wed, 24 Feb 2021 03:49:15 -0800 (PST)
Received: from ndr730u.nd.solarflarecom.com ([182.71.24.30])
        by smtp.googlemail.com with ESMTPSA id
 q23sm2533479pfl.123.2021.02.24.03.49.12
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Wed, 24 Feb 2021 03:49:15 -0800 (PST)
From: Gautam Dawar <gdawar.xilinx@gmail.com>
To: mst@redhat.com
Cc: martinh@xilinx.com, hanand@xilinx.com, gdawar@xilinx.com,
        Gautam Dawar <gdawar.xilinx@gmail.com>,
        Jason Wang <jasowang@redhat.com>,
        Zhu Lingshan <lingshan.zhu@intel.com>, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] vhost_vdpa: fix the missing irq_bypass_unregister_producer()
 invocation
Date: Wed, 24 Feb 2021 17:18:45 +0530
Message-Id: <20210224114845.104173-1-gdawar.xilinx@gmail.com>
X-Mailer: git-send-email 2.30.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When qemu with vhost-vdpa netdevice is run for the first time,
it works well. But after the VM is powered off, the next qemu run
causes kernel panic due to a NULL pointer dereference in
irq_bypass_register_producer().

When the VM is powered off, vhost_vdpa_clean_irq() misses on calling
irq_bypass_unregister_producer() for irq 0 because of the existing check.

This leaves stale producer nodes, which are reset in
vhost_vring_call_reset() when vhost_dev_init() is invoked during the
second qemu run.

As the node member of struct irq_bypass_producer is also initialized
to zero, traversal on the producers list causes crash due to NULL
pointer dereference.

Fixes: 2cf1ba9a4d15c ("vhost_vdpa: implement IRQ offloading in vhost_vdpa")
Bugzilla: https://bugzilla.kernel.org/show_bug.cgi?id=211711
Signed-off-by: Gautam Dawar <gdawar.xilinx@gmail.com>
Acked-by: Jason Wang <jasowang@redhat.com>
---
 drivers/vhost/vdpa.c | 8 ++------
 1 file changed, 2 insertions(+), 6 deletions(-)

```
#### [PATCH kvm-unit-tests v2 1/4] x86: hyperv_stimer: keep SINT number parameter in 'struct stimer'
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 12102135
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5657CC433DB
	for <kvm@archiver.kernel.org>; Wed, 24 Feb 2021 16:39:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0C2E664EBA
	for <kvm@archiver.kernel.org>; Wed, 24 Feb 2021 16:39:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235390AbhBXQjI (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 24 Feb 2021 11:39:08 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:28910 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S235406AbhBXQhV (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 24 Feb 2021 11:37:21 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1614184555;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=ul0Yt6zeiwAM8weYOyOSJ2OiEPiScZ2rMxR8/x//HFM=;
        b=GWJwJX4fvOpXLogQ5jfA0OnxicsIOGhgROOC2qozo7lolTq3HrxdaE+JaSETOqzPlMl9B8
        vvhMTKcJm7nm6cm5yNiFulMtuIypya5ypQxeVdOHpAxIoy15lSUA1KX/h1O4yIDTkimI69
        bqdEYpaE7X6nzZfHsRNsfR5Jgl/bGpY=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-330-wGC310LYMCSX2952f1eVjw-1; Wed, 24 Feb 2021 11:35:52 -0500
X-MC-Unique: wGC310LYMCSX2952f1eVjw-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 2D497BBEF3
        for <kvm@vger.kernel.org>; Wed, 24 Feb 2021 16:35:51 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.221])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 265D419C71;
        Wed, 24 Feb 2021 16:35:49 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Subject: [PATCH kvm-unit-tests v2 1/4] x86: hyperv_stimer: keep SINT number
 parameter in 'struct stimer'
Date: Wed, 24 Feb 2021 17:35:44 +0100
Message-Id: <20210224163547.197100-2-vkuznets@redhat.com>
In-Reply-To: <20210224163547.197100-1-vkuznets@redhat.com>
References: <20210224163547.197100-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

As a preparation to enabling direct synthetic timers support stop
passing SINT number to stimer_start.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 x86/hyperv_stimer.c | 28 +++++++++++++++++++---------
 1 file changed, 19 insertions(+), 9 deletions(-)

```
