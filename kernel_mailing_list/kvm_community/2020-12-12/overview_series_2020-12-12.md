#### [GIT PULL] Final batch of KVM changes for Linux 5.10
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11970127
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-20.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,
	SPF_HELO_NONE,SPF_PASS autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1CA1DC4361B
	for <kvm@archiver.kernel.org>; Sat, 12 Dec 2020 15:55:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D105322AAD
	for <kvm@archiver.kernel.org>; Sat, 12 Dec 2020 15:55:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2439283AbgLLPzM (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sat, 12 Dec 2020 10:55:12 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:21518 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726133AbgLLPzM (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sat, 12 Dec 2020 10:55:12 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1607788426;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=49p9jAWEo46JDV7PkNFs54HnwrvxIQVr2zd4nKr9GNo=;
        b=JHDxovB5UOYiXMOFlwoZHMcm9cz1z7V25w0BRaVi7Rx9ZdhaKGSQlNm9ccMWN5grnV12oM
        RAWEla/BSERfIp0mmgl0vOIL2iXxhixaUAh7OTQkX/VX9z6ReXSvMAnfLoDr5Qp97KXTv2
        zaRfq+Tk8NxHtjLesWzgCLHcgRMEdWg=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-235-HONcu8xoOe-mZTnguP9Gcg-1; Sat, 12 Dec 2020 10:53:44 -0500
X-MC-Unique: HONcu8xoOe-mZTnguP9Gcg-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 0B3FE180A095;
        Sat, 12 Dec 2020 15:53:43 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id ACECC63BA7;
        Sat, 12 Dec 2020 15:53:42 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: torvalds@linux-foundation.org
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [GIT PULL] Final batch of KVM changes for Linux 5.10
Date: Sat, 12 Dec 2020 10:53:42 -0500
Message-Id: <20201212155342.812596-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linus,

The following changes since commit 9a2a0d3ca163fc645991804b8b032f7d59326bb5:

  kvm: x86/mmu: Fix get_mmio_spte() on CPUs supporting 5-level PT (2020-11-27 11:14:27 -0500)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to 111d0bda8eeb4b54e0c63897b071effbf9fd9251:

  tools/kvm_stat: Exempt time-based counters (2020-12-11 19:18:51 -0500)

----------------------------------------------------------------
Bugfixes for ARM, x86 and tools.

----------------------------------------------------------------
Jacob Xu (1):
      kvm: svm: de-allocate svm_cpu_data for all cpus in svm_cpu_uninit()

Maciej S. Szmigiero (2):
      selftests: kvm/set_memory_region_test: Fix race in move region test
      KVM: mmu: Fix SPTE encoding of MMIO generation upper half

Paolo Bonzini (1):
      Merge tag 'kvmarm-fixes-5.10-5' of git://git.kernel.org/.../kvmarm/kvmarm into HEAD

Rick Edgecombe (1):
      kvm: x86/mmu: Use cpuid to determine max gfn

Stefan Raspl (1):
      tools/kvm_stat: Exempt time-based counters

Yanan Wang (3):
      KVM: arm64: Fix memory leak on stage2 update of a valid PTE
      KVM: arm64: Fix handling of merging tables into a block entry
      KVM: arm64: Add usage of stage 2 fault lookup level in user_mem_abort()

 Documentation/virt/kvm/mmu.rst                     |  2 +-
 arch/arm64/include/asm/esr.h                       |  1 +
 arch/arm64/include/asm/kvm_emulate.h               |  5 +++++
 arch/arm64/kvm/hyp/pgtable.c                       | 17 ++++++++++++++-
 arch/arm64/kvm/mmu.c                               | 11 ++++++++--
 arch/x86/kvm/mmu/spte.c                            |  4 ++--
 arch/x86/kvm/mmu/spte.h                            | 25 ++++++++++++++++------
 arch/x86/kvm/mmu/tdp_mmu.c                         |  4 ++--
 arch/x86/kvm/svm/svm.c                             |  4 ++--
 tools/kvm/kvm_stat/kvm_stat                        |  6 +++++-
 .../testing/selftests/kvm/set_memory_region_test.c | 17 +++++++++++----
 11 files changed, 74 insertions(+), 22 deletions(-)
```
#### [PATCH 1/9] KVM: arm64: vgic-v3: Fix some error codes when setting RDIST base
##### From: Eric Auger <eric.auger@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Auger <eric.auger@redhat.com>
X-Patchwork-Id: 11970339
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 69E24C4361B
	for <kvm@archiver.kernel.org>; Sat, 12 Dec 2020 18:57:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2567921D46
	for <kvm@archiver.kernel.org>; Sat, 12 Dec 2020 18:57:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2407752AbgLLSwQ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sat, 12 Dec 2020 13:52:16 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:44081 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726167AbgLLSv7 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sat, 12 Dec 2020 13:51:59 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1607799032;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=aRu7FhoYj+iXi1m//Yx7IJ9OctRxhpZYB5NeyA8SUmk=;
        b=A0+KL0oe9NG5zExx2UkPnw7TeMzjNnciFy+QplK+cYVLLeUV4bin+iEFk3AjDcao6rP/Od
        Io74xXZYcLt2wIzQhhrRFZYlHg0NRuZNRAKh3wfXu+43WkbGh8cKzj2cjKvJW/jqa+mxQV
        ih1x0mqHBG1y0XuvhpftQZpsWbY5ork=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-6-HqWWyWeLNnqf-MJRL5v7cQ-1; Sat, 12 Dec 2020 13:50:30 -0500
X-MC-Unique: HqWWyWeLNnqf-MJRL5v7cQ-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 3246A107ACE3;
        Sat, 12 Dec 2020 18:50:29 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-115-41.ams2.redhat.com [10.36.115.41])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 492F01F069;
        Sat, 12 Dec 2020 18:50:26 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu, maz@kernel.org, drjones@redhat.com
Cc: alexandru.elisei@arm.com, james.morse@arm.com,
        julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
        shuah@kernel.org, pbonzini@redhat.com
Subject: [PATCH 1/9] KVM: arm64: vgic-v3: Fix some error codes when setting
 RDIST base
Date: Sat, 12 Dec 2020 19:50:02 +0100
Message-Id: <20201212185010.26579-2-eric.auger@redhat.com>
In-Reply-To: <20201212185010.26579-1-eric.auger@redhat.com>
References: <20201212185010.26579-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM_DEV_ARM_VGIC_GRP_ADDR group doc says we should return
-EEXIST in case the base address of the redist is already set.
We currently return -EINVAL.

However we need to return -EINVAL in case a legacy REDIST address
is attempted to be set while REDIST_REGIONS were set. This case
is discriminated by looking at the count field.

Signed-off-by: Eric Auger <eric.auger@redhat.com>
---
 arch/arm64/kvm/vgic/vgic-mmio-v3.c | 9 +++++++--
 1 file changed, 7 insertions(+), 2 deletions(-)

```
#### [PATCH 1/2 v5] KVM: nSVM: Check reserved values for 'Type' and invalid vectors in EVENTINJ
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11969781
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	UNPARSEABLE_RELAY,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id CC713C433FE
	for <kvm@archiver.kernel.org>; Sat, 12 Dec 2020 00:56:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9BEC82336F
	for <kvm@archiver.kernel.org>; Sat, 12 Dec 2020 00:56:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2437956AbgLLAvN (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 11 Dec 2020 19:51:13 -0500
Received: from aserp2130.oracle.com ([141.146.126.79]:42102 "EHLO
        aserp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2437957AbgLLAvL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 11 Dec 2020 19:51:11 -0500
Received: from pps.filterd (aserp2130.oracle.com [127.0.0.1])
        by aserp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 0BC0nS4i166428;
        Sat, 12 Dec 2020 00:50:28 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=corp-2020-01-29;
 bh=6b7bkdK3RairZuKEql1fqwFQvoSZbDq3HT3Ffh/Rs7Y=;
 b=DH5wTzuMOXtLwp3c3EZ36vBCfeALBfWoY1XMl4diwg+8itGHPpORVjgpvDBoew65lk8U
 5et8g1621PH/NvjRaWPD66g8hrmjit4N6EWN6rkvxmDBtWZbP3ki5ki0RX0K5cOemZ/2
 5LymsM5gAIqDdPHDvOVcKDwJ+BcAM2m5FctA4s/00JImz5ta9CPAuvZEt8Jn80rDJcqq
 i9d5hr3pTwyM2RFVlMZDdFF4WaW/+k4oekUUiKrrVmd+jTUEfE5OzBP6GwdDXFntlMhD
 Uz4aNhfpssj8D545Bgh2ZHBrHhC04Twz4tfmvjScQlBWvKc8afs9p5or/LKZmw/uBS/R NQ==
Received: from aserp3030.oracle.com (aserp3030.oracle.com [141.146.126.71])
        by aserp2130.oracle.com with ESMTP id 35ckcb00vg-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Sat, 12 Dec 2020 00:50:28 +0000
Received: from pps.filterd (aserp3030.oracle.com [127.0.0.1])
        by aserp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 0BC0ixP2173947;
        Sat, 12 Dec 2020 00:50:28 GMT
Received: from userv0121.oracle.com (userv0121.oracle.com [156.151.31.72])
        by aserp3030.oracle.com with ESMTP id 358ksu96dp-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Sat, 12 Dec 2020 00:50:27 +0000
Received: from abhmp0019.oracle.com (abhmp0019.oracle.com [141.146.116.25])
        by userv0121.oracle.com (8.14.4/8.13.8) with ESMTP id 0BC0oQJH022915;
        Sat, 12 Dec 2020 00:50:26 GMT
Received: from nsvm-sadhukhan.osdevelopmeniad.oraclevcn.com (/100.100.230.216)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Fri, 11 Dec 2020 16:50:26 -0800
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, seanjc@google.com, jmattson@google.com
Subject: [PATCH 1/2 v5] KVM: nSVM: Check reserved values for 'Type' and
 invalid vectors in EVENTINJ
Date: Sat, 12 Dec 2020 00:50:18 +0000
Message-Id: <20201212005019.6807-2-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.27.0
In-Reply-To: <20201212005019.6807-1-krish.sadhukhan@oracle.com>
References: <20201212005019.6807-1-krish.sadhukhan@oracle.com>
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9832
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxlogscore=999
 suspectscore=0
 bulkscore=0 malwarescore=0 phishscore=0 mlxscore=0 spamscore=0
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2012120003
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9832
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 bulkscore=0
 mlxlogscore=999
 priorityscore=1501 mlxscore=0 suspectscore=0 adultscore=0 phishscore=0
 malwarescore=0 impostorscore=0 lowpriorityscore=0 clxscore=1015
 spamscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2012120004
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

According to sections "Canonicalization and Consistency Checks" and "Event
Injection" in APM vol 2

    VMRUN exits with VMEXIT_INVALID error code if either:
      - Reserved values of TYPE have been specified, or
      - TYPE = 3 (exception) has been specified with a vector that does not
	correspond to an exception (this includes vector 2, which is an NMI,
	not an exception).

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 arch/x86/include/asm/svm.h |  4 ++++
 arch/x86/kvm/svm/nested.c  | 15 +++++++++++++++
 2 files changed, 19 insertions(+)

```
