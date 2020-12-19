

#### [PATCH 0/4] KVM: x86/mmu: Bug fixes and cleanups in get_mmio_spte()
##### From: Sean Christopherson <seanjc@google.com>

```c
From patchwork Fri Dec 18 00:31:35 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 11981047
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5A5C5C4361B
	for <kvm@archiver.kernel.org>; Fri, 18 Dec 2020 00:32:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 229FB23371
	for <kvm@archiver.kernel.org>; Fri, 18 Dec 2020 00:32:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726846AbgLRAcd (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 17 Dec 2020 19:32:33 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:44644 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725930AbgLRAcd (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 17 Dec 2020 19:32:33 -0500
Received: from mail-qt1-x84a.google.com (mail-qt1-x84a.google.com
 [IPv6:2607:f8b0:4864:20::84a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id B529EC061794
        for <kvm@vger.kernel.org>; Thu, 17 Dec 2020 16:31:52 -0800 (PST)
Received: by mail-qt1-x84a.google.com with SMTP id f33so549040qtb.1
        for <kvm@vger.kernel.org>; Thu, 17 Dec 2020 16:31:52 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=2tzta+SNMsYxKKonR8VaQ9Msx9ezDvobAtQZxP1CmTo=;
        b=amSSz5zGcCHdNrtCi5FrIruhHpn5OoUl6IA1/X5JxM4N7MvhDZqrXJM2eyE1xgR8Rr
         2QaQDE8gdcMULMMy6eI97mlfZY1x2Bspoba0n9tpQJ/S3IHiVUSz51ZWcN/+iUgAFwUI
         1DhsZWhpwetS7/vedXEQ4ILtQYKUVeHMfJNWvXviUwWirkQw6fXeP5iWOcZ6bn5KoQra
         T+d6Q/TwEw+2FMgQ8SJFBZvemoXfGI/t6hZJkw3+NNSrTy5l+KYoKENttqfPB+d2ixgZ
         UV6fdyoL7wn5XxXyBBukMU2qMPBhzHmOn/Wfupuci1GTBphgBB8GXVJxjtVlsXgIUHrj
         ueSQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:message-id:mime-version
         :subject:from:to:cc;
        bh=2tzta+SNMsYxKKonR8VaQ9Msx9ezDvobAtQZxP1CmTo=;
        b=Vspablg+puhN+qikOwspso5K9WOfN3j0gbK7HBEHWPw1s/29x6KPiF/gLQuv9r5Eyy
         07i/DEvL6/JpIPXfm+cA0X3ppEKr2uU3P9rXUw9IGaipX1lN5EogP9j+CFM1xaTla31k
         EXMao31CIlMMiyXcm/bhyAbU5BrvxEB/wH3RwUtKV9DBLT9enHh9MFruyRnpDoPrFsYM
         CXFzI9Fafhd4F7ZxvzUJSUXXPp/nuAZ4OLsxd4wWUOcqEuQO/sjSw6FKolzj5hpZRB5C
         ND4TjcllcFUfDZj1bGmgCOeOomHxjSiCz8a0He7WNtSFyNa2BiExZlOlZH6iQmDABPmF
         SbAg==
X-Gm-Message-State: AOAM5319ASM0GbQ0xqBR8Uz8VOopdDhJ2FBXYnN6tnE74SkfjbcKANFa
        kG6+r/mw4C3BKxuqs1HynznuZ2XAqzc=
X-Google-Smtp-Source: 
 ABdhPJyP8JnZK9FrE2u34potBYnzNLsxVsqEiU4W380aT+tsp9or0rO/5iX8TOjLzl9M1V6ApI50oqRNUWk=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:1ea0:b8ff:fe73:50f5])
 (user=seanjc job=sendgmr) by 2002:a05:6214:184a:: with SMTP id
 d10mr1855912qvy.41.1608251511737; Thu, 17 Dec 2020 16:31:51 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Thu, 17 Dec 2020 16:31:35 -0800
Message-Id: <20201218003139.2167891-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.29.2.684.gfbc64c5ab5-goog
Subject: [PATCH 0/4] KVM: x86/mmu: Bug fixes and cleanups in get_mmio_spte()
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Ben Gardon <bgardon@google.com>,
        Richard Herbert <rherbert@sympatico.ca>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Two fixes for bugs that were introduced along with the TDP MMU (though I
strongly suspect only the one reported by Richard, fixed in patch 2/4, is
hittable in practice).  Two additional cleanup on top to try and make the
code a bit more readable and shave a few cycles.

Sean Christopherson (4):
  KVM: x86/mmu: Use -1 to flag an undefined spte in get_mmio_spte()
  KVM: x86/mmu: Get root level from walkers when retrieving MMIO SPTE
  KVM: x86/mmu: Use raw level to index into MMIO walks' sptes array
  KVM: x86/mmu: Optimize not-present/MMIO SPTE check in get_mmio_spte()

 arch/x86/kvm/mmu/mmu.c     | 53 +++++++++++++++++++++-----------------
 arch/x86/kvm/mmu/tdp_mmu.c |  9 ++++---
 arch/x86/kvm/mmu/tdp_mmu.h |  4 ++-
 3 files changed, 39 insertions(+), 27 deletions(-)
```
#### [PATCH v4 0/3] KVM: selftests: Cleanups, take 2
##### From: Andrew Jones <drjones@redhat.com>

```c
From patchwork Fri Dec 18 14:17:31 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11982059
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-10.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id CAD9EC3526B
	for <kvm@archiver.kernel.org>; Fri, 18 Dec 2020 14:19:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 80CBA23A00
	for <kvm@archiver.kernel.org>; Fri, 18 Dec 2020 14:19:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727668AbgLROTL (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 18 Dec 2020 09:19:11 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:48310 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726047AbgLROTK (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 18 Dec 2020 09:19:10 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1608301064;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=CmkwoaE0VgaOpvq0Fe5n9FUGHZ4XeJSYkI4GajNOFiY=;
        b=J+YPLyJK/e5XoAvF134yugWgFwVXIlAwWMKwGnpHiJQ53s/MSl8Pd1i+TL+cVgiZviQWcC
        8anNjRF2fIa4mgArUrnWK1K/B63nuqNnGy9b/bq8GHE6DLYYJySOgOrQDd76zrL06dUDTc
        AAtvuDCBUDHoNqzPBpvuseYJ9/wwP2g=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-244-cfQbNb2ZML-NFCj6p709MQ-1; Fri, 18 Dec 2020 09:17:42 -0500
X-MC-Unique: cfQbNb2ZML-NFCj6p709MQ-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id C19B8190A7A0;
        Fri, 18 Dec 2020 14:17:40 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.40.192.59])
        by smtp.corp.redhat.com (Postfix) with ESMTP id B80A22CFB1;
        Fri, 18 Dec 2020 14:17:35 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, borntraeger@de.ibm.com, frankja@linux.ibm.com,
        bgardon@google.com, peterx@redhat.com
Subject: [PATCH v4 0/3] KVM: selftests: Cleanups, take 2
Date: Fri, 18 Dec 2020 15:17:31 +0100
Message-Id: <20201218141734.54359-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series attempts to clean up demand_paging_test, dirty_log_perf_test,
and dirty_log_test by factoring out common code, creating some new API
along the way. It also splits include/perf_test_util.h into a more
conventional header and source pair.

I've tested on x86 and AArch64 (one config each), but not s390x.

v4:
 - dropped "KVM: selftests: dirty_log_test: Remove create_vm" patch
 - Rebased on latest kvm/queue (patches applied cleanly)
 - Ensured dirty-ring was enabled on x86 when testing

v3:
 - Rebased remaining four patches from v2 onto kvm/queue
 - Picked up r-b's from Peter and Ben

v2: https://www.spinics.net/lists/kvm/msg228711.html   

Thanks,
drew


Andrew Jones (3):
  KVM: selftests: Factor out guest mode code
  KVM: selftests: Use vm_create_with_vcpus in create_vm
  KVM: selftests: Implement perf_test_util more conventionally

 tools/testing/selftests/kvm/Makefile          |   2 +-
 .../selftests/kvm/demand_paging_test.c        | 118 ++++---------
 .../selftests/kvm/dirty_log_perf_test.c       | 145 +++++----------
 tools/testing/selftests/kvm/dirty_log_test.c  | 125 ++++---------
 .../selftests/kvm/include/guest_modes.h       |  21 +++
 .../testing/selftests/kvm/include/kvm_util.h  |   9 +
 .../selftests/kvm/include/perf_test_util.h    | 167 ++----------------
 tools/testing/selftests/kvm/lib/guest_modes.c |  70 ++++++++
 tools/testing/selftests/kvm/lib/kvm_util.c    |   9 +-
 .../selftests/kvm/lib/perf_test_util.c        | 134 ++++++++++++++
 10 files changed, 363 insertions(+), 437 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/include/guest_modes.h
 create mode 100644 tools/testing/selftests/kvm/lib/guest_modes.c
 create mode 100644 tools/testing/selftests/kvm/lib/perf_test_util.c
```
#### [PATCH v1 0/4] s390/kvm: fix MVPG when in VSIE
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
From patchwork Fri Dec 18 14:18:07 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 11982067
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A3345C4361B
	for <kvm@archiver.kernel.org>; Fri, 18 Dec 2020 14:19:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7C0F923AAA
	for <kvm@archiver.kernel.org>; Fri, 18 Dec 2020 14:19:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727102AbgLROS7 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 18 Dec 2020 09:18:59 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:55166 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725908AbgLROS6 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 18 Dec 2020 09:18:58 -0500
Received: from pps.filterd (m0098399.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0BIEDEnT040950;
        Fri, 18 Dec 2020 09:18:18 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=Hb2vIskaEuEzm8cbxDywKvyMNWrHp7cUGkREIFvkH3I=;
 b=RQmf/u2MgmVv/pU1R2MqfPcromLVjaxvE4kE9Z7+pbbfR4nJAW3PEZJOAe4fjpUx7BmN
 5v8BzOr6pUrSUUBS3HFPqimHIbwqeBQY0DeiHNUaSlrqb65WQ3eYfycuqK3xYLLq5Ziq
 +ga0kuAN4ohOKMad0WZ/QboS7FEs/Kw62eLbWx2oYmMMKQoRTQegIyJLm/Bx8GkZVeu3
 /TQlFwppwW0DxkPeYOeQ+ZD1V06RN8UwXviEC8dNwzKQoumfnbBExeu0QSa5xFustnR2
 FcoXKzA9Pn0tiYgW1PAeh+WzTpHmTmB2BvPwl6VwwhEJBDBPCyufB1kheLFsX5MjOWYD 5g==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 35gx0cg55q-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 18 Dec 2020 09:18:18 -0500
Received: from m0098399.ppops.net (m0098399.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0BIEDTSv041680;
        Fri, 18 Dec 2020 09:18:17 -0500
Received: from ppma04fra.de.ibm.com (6a.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.106])
        by mx0a-001b2d01.pphosted.com with ESMTP id 35gx0cg54x-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 18 Dec 2020 09:18:17 -0500
Received: from pps.filterd (ppma04fra.de.ibm.com [127.0.0.1])
        by ppma04fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0BIEGeoM015047;
        Fri, 18 Dec 2020 14:18:15 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma04fra.de.ibm.com with ESMTP id 35cng8bbw3-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 18 Dec 2020 14:18:15 +0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0BIEICh842467650
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 18 Dec 2020 14:18:12 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 34A24A4060;
        Fri, 18 Dec 2020 14:18:12 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id CF5D7A405B;
        Fri, 18 Dec 2020 14:18:11 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.12.102])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 18 Dec 2020 14:18:11 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: linux-kernel@vger.kernel.org
Cc: borntraeger@de.ibm.com, frankja@linux.ibm.com, david@redhat.com,
        kvm@vger.kernel.org, linux-s390@vger.kernel.org
Subject: [PATCH v1 0/4] s390/kvm: fix MVPG when in VSIE
Date: Fri, 18 Dec 2020 15:18:07 +0100
Message-Id: <20201218141811.310267-1-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2020-12-18_09:2020-12-18,2020-12-18 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0 adultscore=0
 clxscore=1015 suspectscore=0 mlxlogscore=790 spamscore=0 impostorscore=0
 mlxscore=0 priorityscore=1501 lowpriorityscore=0 phishscore=0
 malwarescore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2012180095
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The current handling of the MVPG instruction when executed in a nested
guest is wrong, and can lead to the nested guest hanging.

This patchset fixes the behaviour to be more architecturally correct,
and fixes the hangs observed.

Claudio Imbrenda (4):
  s390/kvm: VSIE: stop leaking host addresses
  s390/kvm: extend guest_translate for MVPG interpretation
  s390/kvm: add kvm_s390_vsie_mvpg_check needed for VSIE MVPG
  s390/kvm: VSIE: correctly handle MVPG when in VSIE

 arch/s390/kvm/gaccess.c | 88 ++++++++++++++++++++++++++++++++++++++---
 arch/s390/kvm/gaccess.h |  3 ++
 arch/s390/kvm/vsie.c    | 78 +++++++++++++++++++++++++++++++++---
 3 files changed, 159 insertions(+), 10 deletions(-)
```
